using System;
using System.IO;
using System.Text;

namespace OKPOEAuthServer
{
    public class Offsets
    {
        private static ulong SendPacketOffset = 0x1A31410; //NEW: 48 89 5C 24 10 48 89 74 24 18 55 57 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 8B F2 48 8B D9 45 33 F6
        private static ulong AntiPacketOffset = 0x1A30DB0; //48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 48 8B D9 48 8B B9 28 01 00 00 48 85 FF 74 58 48 8B
        private static ulong IngameStateOffset = 0x2EE1AE0; //48 8b 05 ? ? ? ? 48 89 07 48 8b 05 ? ? ? ? 48 89         old: 49 8b 06 4c 89 64 24 20 4d 8b cd 49 8b ce ff 50 48 84 c0 0f 85 ? 0 0 0 41 38 46 0a, 
        private static ulong LightsOffset = 0xF42386; //0F 28 F3 F3 0f 11 49 2c 0f 57 c0 48 8d 4c 24 48 broken
        private static ulong SpawnOffset = 0x1CE722; //new: 48 8b ac 24 80 00 00 00 48 83 c4 50 41 5e 5f 5e c3 41 b9 01 00 00 00 4c 8b c1 48    ADD RSP, 50

        private static ulong UploadDump = 0x1A3A000; //40 55 56 48 8d ac 24 b8 f6 ff ff 48 81 ec 48 0a 00 00
        private static ulong PointerLocalEntity = IngameStateOffset; //48 8b b9 ? ? ? ? 48 85 db 74 ?? 48 89 74 24 40 BE FF FF FF FF 8B C6 F0 0F C1 43 08, 48 39 2D ? ? ? ? 0F 85 A8 01 00 00 BE 38 01 00 00 65 48 8B 04 25 58 00 00 00
        private static ulong ClientMessageOffset = 0x233CFD8; //48 89 5c 24 08 48 89 6c 24 18 56 57 41 56 b8 ? ? ? ? e8 ? ? ? ? 
        private static ulong OnSkillGemLevelUpOffset = 0x85F680; //40 53 48 83 ec 50 48 8b d9 0f b6 05 ? ? ? ? 3c 02 74 70 45 33 c0  "SkillGemLevelUp"
        private static ulong PointerInventories = 0x2D1BA48; //48 8b 1d ? ? ? ? 48 8b 3d ? ? ? ? 48 3b df 74 ? 66 66 ?

        private static ulong ShowHPBars = 0x59C81D; //7C 1A 48 8b CE e8 ? ? ? ? 8b 4e 2c 2b c8 41 0f 48 cf

        private static ulong CameraZoom = 0x276C93; //48 8D 44 24 20 0F 2F 11 48 0F 43 C1   add  5bytes

        private static ulong ClientVersion = 0x2562895; //scan the current version num as a string

        private static ulong OnPortalLabelLoad = 0xD8F622; //90 48 8b 44 24 48 48 85 c0 74 29, rdx = portal's label, can get trial names with this

        private static ulong RevealMap = 0x1EB10A6;

        private static ulong MultiClient = 0x12EE28;

        ulong[] OffsetList;

        public ulong GetOffsetFromFile(string filename, int line_num)
        {
            int current_line_count = 0;
            using (var fileStream = File.OpenRead(filename))
            using (var streamReader = new StreamReader(fileStream, Encoding.UTF8))
            {
                String line;
                while ((line = streamReader.ReadLine()) != null)
                {
                    // Process line
                    if(line_num == current_line_count)
                    {    
                        return Convert.ToUInt64(line.Trim(), 16);
                    }

                    current_line_count++;
                }
            }

            return 0;
        }

        public ulong[] FormOffsetList()
        {
            this.OffsetList = new ulong[15];

            //OffsetList[0] = SendPacketOffset;   //order of offsets in file , one offset per line in your Offsets.txt file
            //OffsetList[1] = IngameStateOffset;
            //OffsetList[2] = LightsOffset;
            //OffsetList[3] = SpawnOffset;
            //OffsetList[4] = UploadDump;
            //OffsetList[5] = PointerLocalEntity;
            //OffsetList[6] = ClientMessageOffset;
            //OffsetList[7] = OnSkillGemLevelUpOffset;
            //OffsetList[8] = PointerInventories;
            //OffsetList[9] = CameraZoom;
            //OffsetList[10] = ShowHPBars;
            //OffsetList[11] = AntiPacketOffset;
            //OffsetList[12] = ClientVersion;
            //OffsetList[13] = OnPortalLabelLoad;
            //OffsetList[14] = RevealMap;
            //OffsetList[15] = MultiClient

            for(int i = 0; i < 15; i++)
            {
                OffsetList[i] = GetOffsetFromFile("./Offsets.txt", i);
                //Console.WriteLine("{0}", OffsetList[i]);
            }

            return this.OffsetList;
        }

        public ulong GetSum()
        {
            ulong sum = 0;

            sum += SendPacketOffset;
            sum += IngameStateOffset;
            sum += LightsOffset;
            sum += SpawnOffset;
            sum += UploadDump;
            sum += PointerLocalEntity;
            sum += ClientMessageOffset;
            sum += OnSkillGemLevelUpOffset;
            sum += PointerInventories;
            sum += CameraZoom;
            sum += ShowHPBars;
            sum += AntiPacketOffset;
            sum += OnPortalLabelLoad;
            return sum;
        }
    }
}
