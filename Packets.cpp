#include "Packets.hpp"
#include "AutoPlayer.hpp"
#include "NetLogger.hpp"

std::queue<PacketWriter*> SendPacketQueue; 
std::vector<uint16_t> BlockedList;
std::vector<uint16_t> IgnoredList;

extern AutoPlayer* g_Robot;
extern NetLogger* g_ProtectionServer;

int rand_lim(int limit)
{
	int divisor = RAND_MAX / (limit + 1);
	int retval;

	do {
		retval = rand() / divisor;
	} while (retval > limit);

	return retval;
}

LPBYTE PacketHelper::ToPacketFormat(const CHAR* __in input)
{
	char fixedString[2048] = { 0 };

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

	LPBYTE bytestring = (unsigned char*)malloc((j * 2) + 1);
	
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

std::string PacketHelper::ToString(LPBYTE packetStr, int byteLength)
{
	if (byteLength <= 0)
		return NULL;

	std::string newStr = string();
	CHAR* convertStr = (CHAR*)malloc(byteLength * 3); //* 3 since 00[ ] an extra 0 with a space for each byte in the str.

	for (int i = 0; i < byteLength; i++) {
		byte ch = packetStr[i];
		sprintf(&convertStr[i], "%.2X", ch);
		newStr.append(&convertStr[i]);
		newStr.append(" ");
	}

	free(convertStr);
	return newStr;
}

int PacketHelper::GetPacketLength(const CHAR* input)
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

uint16_t Opcode;
void PacketHelper::CreatePacket(LPBYTE data, UINT length)
{
		if (length < 0)
			return;

		memcpy(&Opcode, (void*)&data[0], sizeof(uint16_t));

		uint16_t OriginalOpcode = Opcode;
		Opcode = changeEndianness16(Opcode);

		switch (OriginalOpcode)
		{
			case SendOpcodes::Ping: //pings
			case SendOpcodes::Tick:
			{
				return;
			}break;

			case SendOpcodes::PlayerChat:
			{
				if (!g_Robot->Disconnected)
				{
					uint16_t textLen = 0;

					if (length > 4)
					{
						memcpy(&textLen, &data[2], 2);
						textLen = changeEndianness16(textLen);

						if (textLen > 0)
						{
							CHAR text[1024];
							memcpy(text, &data[4], textLen);
							text[textLen] = '\0';

							string chat = string(text);
							if (chat.size() > 0)
								int bytesSent = g_ProtectionServer->SendData(chat);
						}
					}
				}
			}break;

			case SendOpcodes::PartyInvite:
			{
				if (length > 4)
				{
					uint16_t textLen = 0;

					memcpy(&textLen, &data[2], 2);
					textLen = changeEndianness16(textLen);

					if (textLen > 0)
					{
						CHAR text[255];
						memcpy(text, &data[4], textLen);
						text[textLen] = '\0';

						string invitee = string(text);
						int bytesSent = g_ProtectionServer->SendData(invitee);
					}
				}

			}break;

			case SendOpcodes::LaunchAtlasMap:
			{
				uint16_t mapOption = 0;

				memcpy(&mapOption, &data[2], 2);
				mapOption = changeEndianness16(mapOption);

				//if (mapOption == 0x0031)
				//{
				//	memcpy(&data[2], "\x24\x00", 2);
				//}
			}
			break;

			case SendOpcodes::TradePlayer:
			{
				FileIO::Log("[OKPOE LOG] Traded player.\n");
				g_Robot->Attacker->IsBusy = true;
			}break;

			case SendOpcodes::CancelTrade:
			{
				FileIO::Log("[OKPOE LOG] Trade was cancelled.\n");
				g_Robot->Attacker->IsBusy = false;
			}break;

			case SendOpcodes::AcceptTrade:
			{
				FileIO::Log("[OKPOE LOG] Accepted trade!\n");
				g_Robot->Attacker->IsBusy = false;
			}break;

			case SendOpcodes::PlayerInput:
			{
				if (g_Robot->UsingDynamiteHack) //nomral attack to dynamite
				{
					unsigned short input = 0;
					memcpy(&input, &data[10], sizeof(uint16_t));
					if (input == 0x0040)
						memcpy(&data[10], "\x8F\x00", sizeof(uint16_t));
				}

				if (g_Robot->isRecordingMovement == true)
				{
					Vector2 v = { 0 };

					unsigned short input = 0;
					memcpy(&input, &data[10], sizeof(uint16_t));
					
					if (input == changeEndianness16(Input::InputIds::RUN))
					{
						memcpy((void*)&v.X, &data[2], sizeof(uint32_t));
						memcpy((void*)&v.Y, &data[6], sizeof(uint32_t));

						v.X = changeEndianness32(v.X);
						v.Y = changeEndianness32(v.Y);

						printf("X: %d, Y: %d\n", v.X, v.Y);
						char X[10], Y[10];
						char logData[50] = { 0 };
						itoa(v.X, X, 10);
						itoa(v.Y, Y, 10);

						strcpy(logData, X);
						strcat(logData, ", ");
						strcat(logData, Y);
						strcat(logData, "\r\n");

						FileIO::WriteToFile("Movement.txt", (LPBYTE)logData, strlen(logData));
					}	
				}
			}

			case SendOpcodes::EntityInteraction:
			{
				if (g_Robot->UsingDynamiteHack) //nomral attack to dynamite
				{
					unsigned short input = 0;
					memcpy(&input, &data[6], sizeof(uint16_t));
					if (input == 0x0040)
						memcpy(&data[6], "\x8F\x00", sizeof(uint16_t));
				}
			}break;

		};

		//for (auto & element : IgnoredList)
		//	if ((uint16_t)element == (uint16_t)Opcode) //found ignored
		//		return;

		PacketWriter* p = new PacketWriter();

		if (p != nullptr)
		{
			for (int i = 0; i < length; i++)
				p->Write<byte>(data[i]);

			if (g_Robot->isLoggingOutbound)
				SendPacketQueue.push(p);
		}
}

uint16_t PacketHelper::changeEndianness16(uint16_t val)
{
	return (val << 8) | ((val >> 8) & 0x00ff); // right-shift sign-extends, so force to zero
}


uint32_t PacketHelper::changeEndianness32(uint32_t val)
{
	int32_t tmp = (val << 16) |
		((val >> 16) & 0x0000ffff);
	return ((tmp >> 8) & 0x00ff00ff) | ((tmp & 0x00ff00ff) << 8);
}

uint64_t PacketHelper::changeEndianness64(uint64_t val) //might be wrong, check this!
{
	int32_t tmp = (val << 32) |
		((val >> 32) & 0x00000000ffffffff);
	return ((tmp >> 16) & 0x00ff00ff00ff00ff) | ((tmp & 0x00ff00ff) << 16);
}

std::string PacketHelper::randomStr(size_t size)
{
	std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(str.begin(), str.end(), generator);

	return str.substr(0, size);    // assumes 32 < number of characters in str         
}

std::wstring PacketHelper::randomWStr(size_t size)
{
	std::wstring str(L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(str.begin(), str.end(), generator);

	return str.substr(0, size);    // assumes 32 < number of characters in str         
}

void PacketHelper::Send(UINT64 SendClass, LPBYTE Data, UINT64 Length) //non packet-writer version
{
	DWORD pOldProt = 0;
	bool result = VirtualProtect(&Data, Length, PAGE_EXECUTE_READWRITE, &pOldProt);

	if (g_Robot->Disconnected)
	{
		printf("Can't send packet, disconnected...\n");
		return;
	}

	if (result)
	{
		if (SendClass > NULL && !g_Robot->Disconnected)
			SendPacket(SendClass, Data, Length);
	}

	if (Data != nullptr)
	{
		delete Data; Data = nullptr;
	}

}

std::string PacketHelper::string_to_hex(const std::string& in)
{
	std::stringstream ss;

	ss << std::hex << std::setfill('0');
	for (size_t i = 0; in.length() > i; ++i) {
		ss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(in[i]));
	}

	return ss.str();
}

std::string PacketHelper::hex_to_string(const std::string& input)
{
	std::string output;

	if ((input.length() % 2) != 0) {
		throw std::runtime_error("String is not valid length ...");
	}

	size_t cnt = input.length() / 2;

	for (size_t i = 0; cnt > i; ++i) {
		uint32_t s = 0;
		std::stringstream ss;
		ss << std::hex << input.substr(i * 2, 2);
		ss >> s;

		output.push_back(static_cast<unsigned char>(s));
	}

	return output;
}