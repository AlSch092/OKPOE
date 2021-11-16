#include "Packets.hpp"
#include "AutoPlayer.hpp"
std::queue<PacketWriter*> SendPacketQueue; //find new place for this
std::vector<uint16_t> BlockedList;
std::vector<uint16_t> IgnoredList;

extern BOOL isLoggingSendPackets;
extern AutoPlayer* Robot;

int rand_lim(int limit)
{
	int divisor = RAND_MAX / (limit + 1);
	int retval;

	do {
		retval = rand() / divisor;
	} while (retval > limit);

	return retval;
}

LPBYTE PacketHelper::ToPacketFormat(CHAR* input) //literally the worst old func left still... lmao
{

	char fixedString[4096] = { 0 };

	//strip spaces, bad text
	int i; int j = 0;

	for (i = 0; input[i] != '\0'; i++) {
		if ((input[i] >= 'A' && input[i] <= 'F') || (input[i] >= '0' && input[i] <= '9') || (input[i] >= 'a' && input[i] <= 'f'))  {
			fixedString[j] = input[i];
			j++;
		}
		else if (input[i] == ' ') {

		}
		else if (input[i] == '*') {

			int random = rand_lim(15);

			if (random >= 0 && random <= 9) {
				fixedString[j] = random + 0x30;
			}
			else if (random >= 9 && random <= 15) {
				fixedString[j] = random + 0x55;
			}

			j++;
		}
		else {
			return NULL;
		}

	}

	LPBYTE bytestring = (unsigned char*)calloc((sizeof(char)*j * 2) + 1, sizeof(byte));
	
	j = 0;

	for (i = 0; fixedString[i] != '\0'; i++) {

		if (i % 2 == 0) { //even number iterator
			if (fixedString[i] >= 'a' && fixedString[i] <= 'f') {
				bytestring[j] = ((fixedString[i] - 0x57) << 4);

				if (fixedString[i + 1] >= 'A' && fixedString[i + 1] <= 'F') {
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x37);
				}
				else if (fixedString[i + 1] >= '0' && fixedString[i + 1] <= '9') {
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x30);
				}
				else if (fixedString[i + 1] >= 'a' && fixedString[i + 1] <= 'f') {
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x57);
				}
				j++;
				i++;
			}
			else if (fixedString[i] >= '0' && fixedString[i] <= '9') {

				bytestring[j] = ((fixedString[i] - 0x30) << 4);

				if (fixedString[i + 1] >= 'A' && fixedString[i + 1] <= 'F') {
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x37);
				}
				else if (fixedString[i + 1] >= '0' && fixedString[i + 1] <= '9') {
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x30);
				}
				else if (fixedString[i + 1] >= 'a' && fixedString[i + 1] <= 'f') {
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x57);
				}
				j++;
				i++;
			}
			else if (fixedString[i] >= 'A' && fixedString[i] <= 'F') {
				bytestring[j] = ((fixedString[i] - 0x37) << 4);

				if (fixedString[i + 1] >= 'A' && fixedString[i + 1] <= 'F') {
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x37);
				}
				else if (fixedString[i + 1] >= '0' && fixedString[i + 1] <= '9') {
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x30);
				}
				else if (fixedString[i + 1] >= 'a' && fixedString[i + 1] <= 'f') {
					bytestring[j] = bytestring[j] + (fixedString[i + 1] - 0x57);
				}
				j++;
				i++;
			}
		}
	}

	return bytestring;
}

std::string* PacketHelper::ToString(LPBYTE packetStr, int byteLength)
{
	if (byteLength <= 0)
		return NULL;

	std::string* newStr = new std::string();
	CHAR* convertStr = (CHAR*)malloc(byteLength * 3); //* 3 since 00[ ] an extra 0 with a space for each byte in the str.

	for (int i = 0; i < byteLength; i++) {
		byte ch = packetStr[i];
		sprintf(&convertStr[i], "%.2X", ch);
		newStr->append(&convertStr[i]);
		newStr->append(" ");
	}

	free(convertStr);
	return newStr;
}

int PacketHelper::GetPacketLength(CHAR* input)
{
	int length = 0;

	for (int i = 0; input[i] != '\0'; i++) {
		if (input[i] == ' ')
			length = length;
		else
			length++;
	}

	length = length / 2;

	return length;
}

void PacketHelper::CreatePacket(LPBYTE data, UINT length)
{
		if (length < 0)
			return;

		short Opcode;

		memcpy(&Opcode, (void*)&data[0], sizeof(uint16_t));

		Opcode = changeEndianness16(Opcode);

		switch (Opcode)
		{
			case 0x000E: //pings
			case 0x0001:
				return;

			case SendOpcodes::TradePlayer:
			{
				FileIO::Log("[OKPOE LOG] Traded player.\n");
				Robot->IsBusy = true;
			}break;

			case SendOpcodes::CancelTrade:
			{
				FileIO::Log("[OKPOE LOG] Trade was cancelled.\n");
				Robot->IsBusy = false;
			}break;

			case SendOpcodes::AcceptTrade:
			{
				FileIO::Log("[OKPOE LOG] Accepted trade!\n");
				Robot->IsBusy = false;
			}break;

			case 0x0171:
			{
				FileIO::Log("[OKPOE LOG] Entered New Area.\n");
				Robot->EnteredNewArea = true;
				Robot->IsBusy = false;
			}
			break;

			case 0x003C:
			{
				Robot->IsBusy = true;
				uint32_t hash;
				memcpy(&hash, &data[2], 4);
				FileIO::Log("[OKPOE LOG] Entering New Area with hash: %u\n", hash);
			}break;

			case 0x0003: //detach any hooks or apply a stopper
			{
				Robot->IsBusy = true;
				Robot->MonsterList.clear();
				Robot->BlightFoundationList.clear();
				Robot->GroundItemList.clear();
				Robot->EntityList.clear();
				FileIO::Log("[OKPOE LOG] Entering new area.\n");
			}break;

		};

		for (auto & element : IgnoredList)
			if ((uint16_t)element == (uint16_t)Opcode) //found ignored
				return;

		PacketWriter* p = new PacketWriter();

		for (int i = 0; i < length; i++)
			p->Write<byte>(data[i]);

		if (isLoggingSendPackets)
			SendPacketQueue.push(p);
}


UINT16 changeEndianness16(UINT16 val)
{
	return (val << 8) | ((val >> 8) & 0x00ff); // right-shift sign-extends, so force to zero
}


int32_t changeEndianness32(int32_t val)
{
	int32_t tmp = (val << 16) |
		((val >> 16) & 0x00ffff);
	return ((tmp >> 8) & 0x00ff00ff) | ((tmp & 0x00ff00ff) << 8);
}

std::string randomStr(size_t size)
{
	std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(str.begin(), str.end(), generator);

	return str.substr(0, size);    // assumes 32 < number of characters in str         
}

std::wstring randomWStr(size_t size)
{
	std::wstring str(L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(str.begin(), str.end(), generator);

	return str.substr(0, size);    // assumes 32 < number of characters in str         
}

