#pragma once
#include "locale.hpp"
#include "Scripter.hpp"
#include "Hotkeys.hpp"
#include "HideProcess.hpp"
#include "Element.hpp"
#include <vcclr.h>
#include <msclr\marshal_cppstd.h>

static UINT64 gClientBase = 0;
extern std::queue<PacketWriter*> SendPacketQueue;

extern HMODULE g_OurModule;

//global instances
AutoPlayer* g_Robot = NULL;
NetLogger* g_ProtectionServer;

//this needs to go in a file only included once
//make accesssible to .asm file
extern "C"
{
	UINT64 lpCreatePacketFunc = 0;
	UINT64 lpSendPacketFunction = 0;
	UINT64 lpSendPacketReturnAddress = 0;

	UINT64 lpEntitySpawnFunctionAddress = 0;
	UINT64 lpEntitySpawnReturnAddress = 0;

	UINT64 lpEntityLabelSpawnCallbackAddress = 0;
	UINT64 lpEntityLabelSpawnReturnAddress = 0;

	UINT64 lpReduceCPUReturnAddress = 0;

	UINT64 lpHandleKeypress = 0;
	UINT64 lpHotkeyHookReturn = 0;

	UINT64 lpClientMessageReturnAddr = 0;
	UINT64 lpClientMessageHookFunc = 0;

	UINT64 lpOnSkillGemLevelUpHookFunc;
	UINT64 lpOnSkillGemLevelUpReturnAddr;

	UINT64 lpMinimapIconsHookFunc;
	UINT64 lpMinimapIconsReturnAddr;

	UINT64 CPUReducerSleepTime;
}

namespace OKPOE {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Runtime::InteropServices;
	using namespace System::Text;
	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}


	protected:
		Thread^ ReduceRAMThread;
		Thread^ OutPacketThread;
	private: System::Windows::Forms::MenuStrip^  menuStrip_MainMenu;

	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  shutdownToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  scriptingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  updateCheckToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  creditsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  instructionsToolStripMenuItem;



	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip_Packets;
	private: System::Windows::Forms::ToolStripMenuItem^  copyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  clearAllToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  blockOpcodeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ignoreOpcodeToolStripMenuItem;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

private: System::Windows::Forms::ToolStripMenuItem^  functionsToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem1;
private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem1;

private: System::Windows::Forms::ToolStripMenuItem^  runToolStripMenuItem;

private: System::Windows::Forms::ToolTip^  toolTip_Run;
private: System::Windows::Forms::ToolTip^  toolTip_Stop;
private: System::Windows::Forms::ToolTip^  toolTip_LoadScript;
private: System::Windows::Forms::ToolTip^  toolTip_SaveScript;
private: System::Windows::Forms::ToolTip^  toolTip_Download;
private: System::Windows::Forms::OpenFileDialog^  openFileDialog_OutputLogFile;
private: System::Windows::Forms::ToolStripMenuItem^  donateToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  bitcoinToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  ethereumToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  payPalToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  hotkeysToolStripMenuItem;

private: System::Windows::Forms::TabPage^  tabPage_Bot;
private: System::Windows::Forms::GroupBox^  groupBox11;
private: System::Windows::Forms::CheckBox^  checkBox_Relogin;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
private: System::Windows::Forms::GroupBox^  groupBox8;
private: System::Windows::Forms::RadioButton^  radioButton_ReviveCheckpoint;
private: System::Windows::Forms::RadioButton^  radioButton_ReviveTown;
private: System::Windows::Forms::CheckBox^  checkBox_AutoRevive;

private: System::Windows::Forms::CheckBox^  checkBox_EnterAreaTransitions;
private: System::Windows::Forms::GroupBox^  groupBox5;
private: System::Windows::Forms::ComboBox^  comboBox_SkillGemSlot;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::CheckBox^  checkBox_IsTargeting;
private: System::Windows::Forms::GroupBox^  groupBox4;
private: System::Windows::Forms::RadioButton^  radioButton_AutoLootUseBuiltin;
private: System::Windows::Forms::RadioButton^  radioButton_AutoLootUseFile;
private: System::Windows::Forms::CheckBox^  checkBox_AutoLoot;
private: System::Windows::Forms::GroupBox^  groupBox2;

private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::NumericUpDown^  numericUpDown_FlaskES;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::NumericUpDown^  numericUpDown_FlaskMP;
private: System::Windows::Forms::NumericUpDown^  numericUpDown_FlaskHP;
private: System::Windows::Forms::CheckBox^  checkBox_AutoFlask;
private: System::Windows::Forms::TabPage^  tabPage_Packets;
private: System::Windows::Forms::Button^  button_SendPacket;
private: System::Windows::Forms::TextBox^  textBox_SendPacketInput;
private: System::Windows::Forms::CheckBox^  checkBox_LogSP;
private: System::Windows::Forms::ListView^  listView_Packets;
private: System::Windows::Forms::ColumnHeader^  columnHeader_SPLength;
private: System::Windows::Forms::ColumnHeader^  columnHeader_SPOpcode;
private: System::Windows::Forms::ColumnHeader^  columnHeader_SPData;
private: System::Windows::Forms::TabPage^  tabPage_Hacks;
private: System::Windows::Forms::GroupBox^  groupBox7;

private: System::Windows::Forms::Button^  button_AddIgnoredEntity;
private: System::Windows::Forms::TextBox^  textBox_IgnoreEntity;
private: System::Windows::Forms::CheckBox^  checkBox_LogEntity;


private: System::Windows::Forms::GroupBox^  groupBox6;
private: System::Windows::Forms::ComboBox^  comboBox_FollowMovementSkill;
private: System::Windows::Forms::CheckBox^  checkBox_Follow;
private: System::Windows::Forms::TextBox^  textBox_FollowCharName;
private: System::Windows::Forms::GroupBox^  groupBox_Entities;
private: System::Windows::Forms::Label^  label_Exp;
private: System::Windows::Forms::Label^  label_Level;
private: System::Windows::Forms::Label^  label_Status;

private: System::Windows::Forms::Label^  label_GridY;
private: System::Windows::Forms::CheckBox^  checkBox_DisplayPlayerData;
private: System::Windows::Forms::Label^  label_GridX;
private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::Label^  label_PlayerES;
private: System::Windows::Forms::Label^  label_MP;
private: System::Windows::Forms::Label^  label_HP;
private: System::Windows::Forms::GroupBox^  groupBox1;
private: System::Windows::Forms::CheckBox^  checkBox_StopRender;
private: System::Windows::Forms::CheckBox^  checkBox_ReduceCPU;
private: System::Windows::Forms::CheckBox^  checkBox_RAMReduce;
private: System::Windows::Forms::GroupBox^  groupBox_Utilities;







private: System::Windows::Forms::CheckBox^  checkBox_IncreaseLights;


private: System::Windows::Forms::Button^  button_RevealMap;
private: System::Windows::Forms::CheckBox^  checkBox_MapHack;
private: System::Windows::Forms::TabPage^  tabPage_LUA;
private: System::Windows::Forms::GroupBox^  groupBox3;
private: System::Windows::Forms::CheckBox^  checkBox_RandomizingLUAName;
private: System::Windows::Forms::Button^  button_DownloadLUA;
private: System::Windows::Forms::Button^  button_LoadLUA;
private: System::Windows::Forms::Button^  button_SaveLUA;
private: System::Windows::Forms::Button^  button_RunLUA;
private: System::Windows::Forms::Button^  button_StopLUA;
private: System::Windows::Forms::TextBox^  textBox_ScriptText;
private: System::Windows::Forms::TabControl^  tabControl1;
private: System::Windows::Forms::CheckBox^  checkBox_LevelSkillGems;
private: System::Windows::Forms::CheckBox^  checkBox_HookClientMsg;
private: System::Windows::Forms::CheckBox^  checkBox_MuteConsole;

private: System::Windows::Forms::TabPage^  tabPage_TradeBot;





private: System::Windows::Forms::CheckBox^  checkBox_LogRecv;








private: System::Windows::Forms::CheckBox^  checkBox_DebugMode;
private: System::Windows::Forms::GroupBox^  groupBox13;

private: System::Windows::Forms::ListView^  listView1;
private: System::Windows::Forms::CheckBox^  checkBox_LogAutoTradeData;













private: System::Windows::Forms::ColumnHeader^  columnHeader1;
private: System::Windows::Forms::ColumnHeader^  columnHeader2;
private: System::Windows::Forms::ColumnHeader^  columnHeader3;
private: System::Windows::Forms::ColumnHeader^  columnHeader4;





private: System::Windows::Forms::ToolStripMenuItem^  fineprintToolStripMenuItem;
private: System::Windows::Forms::CheckBox^  checkBox_LogHoveredElements;













private: System::Windows::Forms::GroupBox^  groupBox12;
private: System::Windows::Forms::CheckBox^  checkBox_AutoSellEverything;
private: System::Windows::Forms::ComboBox^  comboBox_AutoTradeServer;
private: System::Windows::Forms::TextBox^  textBox_AutoBuyItemName;
private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::ComboBox^  comboBox_WTBExchangeItem;
private: System::Windows::Forms::NumericUpDown^  numericUpDown_AutoBuyExchangeQuantity;
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::NumericUpDown^  numericUpDown_WTBQuantity;

private: System::Windows::Forms::RadioButton^  radioButton_AutoSell;
private: System::Windows::Forms::RadioButton^  radioButton_AutoBuy;

private: System::Windows::Forms::CheckBox^  checkBox_TradeBot;
private: System::Windows::Forms::CheckBox^  checkBox_IsSkillMelee;







private: System::Windows::Forms::GroupBox^  groupBox10;
private: System::Windows::Forms::Button^  button1;

private: System::Windows::Forms::CheckBox^  checkBox_Hotkeys;
private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
private: System::Windows::Forms::CheckBox^  checkBox_Dynamite;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::ComboBox^  comboBox_MovementSkill;



private: System::Windows::Forms::CheckBox^  checkBox_RepeatScript;
private: System::Windows::Forms::Button^  button3;
private: System::Windows::Forms::TextBox^  textBox2;
private: System::Windows::Forms::CheckBox^  checkBox_AutoFlask50;
















private: System::Windows::Forms::ToolStripMenuItem^  languagesToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  chineseCNToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^  englishENToolStripMenuItem;






























































		 Thread^ PlayerInfoThread;
private: System::Windows::Forms::ToolStripMenuItem^  russianRUToolStripMenuItem;
private: System::Windows::Forms::CheckBox^  checkBox_CraftExploit;
private: System::Windows::Forms::CheckBox^  checkBox_VaalSkill;
private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::ComboBox^  comboBox_PortalGemSlot;

private: System::Windows::Forms::CheckBox^  checkBox_UsingTotems;
private: System::Windows::Forms::Button^  button_UnloadDLL;

private: System::Windows::Forms::ComboBox^  comboBox1;
private: System::Windows::Forms::Label^  label12;

private: System::Windows::Forms::GroupBox^  groupBox9;
private: System::Windows::Forms::CheckBox^  checkBox_ShowHPBars;
private: System::Windows::Forms::CheckBox^  checkBox_Zoom;
private: System::Windows::Forms::CheckBox^  checkBox_NullTerrain;
private: System::Windows::Forms::CheckBox^  checkBox_RighteousFire;
private: System::Windows::Forms::GroupBox^  groupBox14;
private: System::Windows::Forms::CheckBox^  checkBox_IsRangedSkill;
private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::NumericUpDown^  numericUpDown_CPUReducerTime;
private: System::Windows::Forms::GroupBox^  groupBox15;
private: System::Windows::Forms::CheckBox^  checkBox_RecordMovement;
private: System::Windows::Forms::Button^  button_PlayBackMovements;
private: System::Windows::Forms::Label^  label_PlayerClass;
private: System::Windows::Forms::CheckBox^  checkBox_LogEntityLabels;
private: System::Windows::Forms::RichTextBox^  richTextBox_PacketPosition;
































private: System::Windows::Forms::RichTextBox^  richTextBox_PacketInspector;
private: System::Windows::Forms::RichTextBox^  richTextBox_PositionCounter;







private: System::Windows::Forms::GroupBox^ groupBox17;
private: System::Windows::Forms::GroupBox^ groupBox16;
private: System::Windows::Forms::Label^ label21;
private: System::Windows::Forms::Label^ label20;
private: System::Windows::Forms::Label^ label19;
private: System::Windows::Forms::TextBox^ textBox_ConvStr;
private: System::Windows::Forms::TextBox^ textBox_32Float;
private: System::Windows::Forms::TextBox^ textBox_16Float;
private: System::Windows::Forms::Label^ label18;
private: System::Windows::Forms::TextBox^ textBox_8Float;
private: System::Windows::Forms::Label^ label16;
private: System::Windows::Forms::Label^ label15;
private: System::Windows::Forms::Label^ label14;
private: System::Windows::Forms::Label^ label13;
private: System::Windows::Forms::TextBox^ textBox_64Int;
private: System::Windows::Forms::TextBox^ textBox_32Int;
private: System::Windows::Forms::TextBox^ textBox_16Int;
private: System::Windows::Forms::TextBox^ textBox_8Int;
private: System::Windows::Forms::ToolStripMenuItem^ bottingToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ loadProfileToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ saveProfileAsToolStripMenuItem;
private: System::Windows::Forms::ComboBox^ comboBox2;
private: System::Windows::Forms::Label^ label17;
private: System::Windows::Forms::CheckBox^ checkBox_TrialHelper;









		 Languages SelectedLanguage = Languages::EN;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->contextMenuStrip_Packets = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->copyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearAllToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->blockOpcodeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ignoreOpcodeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip_MainMenu = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->languagesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->chineseCNToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->englishENToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->russianRUToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->shutdownToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->scriptingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->functionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->runToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bottingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadProfileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveProfileAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->updateCheckToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hotkeysToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->instructionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->creditsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->donateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bitcoinToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ethereumToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->payPalToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fineprintToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolTip_Run = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->button_RunLUA = (gcnew System::Windows::Forms::Button());
			this->toolTip_Stop = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->button_StopLUA = (gcnew System::Windows::Forms::Button());
			this->toolTip_SaveScript = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->button_SaveLUA = (gcnew System::Windows::Forms::Button());
			this->toolTip_LoadScript = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->button_LoadLUA = (gcnew System::Windows::Forms::Button());
			this->toolTip_Download = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->button_DownloadLUA = (gcnew System::Windows::Forms::Button());
			this->openFileDialog_OutputLogFile = (gcnew System::Windows::Forms::OpenFileDialog());
			this->tabPage_Bot = (gcnew System::Windows::Forms::TabPage());
			this->checkBox_TrialHelper = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox15 = (gcnew System::Windows::Forms::GroupBox());
			this->button_PlayBackMovements = (gcnew System::Windows::Forms::Button());
			this->checkBox_RecordMovement = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
			this->button_UnloadDLL = (gcnew System::Windows::Forms::Button());
			this->checkBox_DebugMode = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox11 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox_Relogin = (gcnew System::Windows::Forms::CheckBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox_LevelSkillGems = (gcnew System::Windows::Forms::CheckBox());
			this->radioButton_ReviveCheckpoint = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton_ReviveTown = (gcnew System::Windows::Forms::RadioButton());
			this->checkBox_AutoRevive = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_EnterAreaTransitions = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->checkBox_IsRangedSkill = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_RighteousFire = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_UsingTotems = (gcnew System::Windows::Forms::CheckBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->comboBox_PortalGemSlot = (gcnew System::Windows::Forms::ComboBox());
			this->checkBox_VaalSkill = (gcnew System::Windows::Forms::CheckBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->comboBox_MovementSkill = (gcnew System::Windows::Forms::ComboBox());
			this->checkBox_IsSkillMelee = (gcnew System::Windows::Forms::CheckBox());
			this->comboBox_SkillGemSlot = (gcnew System::Windows::Forms::ComboBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->checkBox_IsTargeting = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->radioButton_AutoLootUseBuiltin = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton_AutoLootUseFile = (gcnew System::Windows::Forms::RadioButton());
			this->checkBox_AutoLoot = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox_AutoFlask50 = (gcnew System::Windows::Forms::CheckBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown_FlaskES = (gcnew System::Windows::Forms::NumericUpDown());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown_FlaskMP = (gcnew System::Windows::Forms::NumericUpDown());
			this->checkBox_AutoFlask = (gcnew System::Windows::Forms::CheckBox());
			this->numericUpDown_FlaskHP = (gcnew System::Windows::Forms::NumericUpDown());
			this->tabPage_Packets = (gcnew System::Windows::Forms::TabPage());
			this->groupBox17 = (gcnew System::Windows::Forms::GroupBox());
			this->richTextBox_PacketPosition = (gcnew System::Windows::Forms::RichTextBox());
			this->groupBox16 = (gcnew System::Windows::Forms::GroupBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->textBox_ConvStr = (gcnew System::Windows::Forms::TextBox());
			this->textBox_32Float = (gcnew System::Windows::Forms::TextBox());
			this->textBox_16Float = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->textBox_8Float = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBox_64Int = (gcnew System::Windows::Forms::TextBox());
			this->textBox_32Int = (gcnew System::Windows::Forms::TextBox());
			this->textBox_16Int = (gcnew System::Windows::Forms::TextBox());
			this->textBox_8Int = (gcnew System::Windows::Forms::TextBox());
			this->richTextBox_PacketInspector = (gcnew System::Windows::Forms::RichTextBox());
			this->richTextBox_PositionCounter = (gcnew System::Windows::Forms::RichTextBox());
			this->checkBox_LogRecv = (gcnew System::Windows::Forms::CheckBox());
			this->button_SendPacket = (gcnew System::Windows::Forms::Button());
			this->textBox_SendPacketInput = (gcnew System::Windows::Forms::TextBox());
			this->checkBox_LogSP = (gcnew System::Windows::Forms::CheckBox());
			this->listView_Packets = (gcnew System::Windows::Forms::ListView());
			this->columnHeader_SPLength = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader_SPOpcode = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader_SPData = (gcnew System::Windows::Forms::ColumnHeader());
			this->tabPage_Hacks = (gcnew System::Windows::Forms::TabPage());
			this->groupBox14 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox_ShowHPBars = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_Zoom = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_IncreaseLights = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_Dynamite = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_MapHack = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_CraftExploit = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox10 = (gcnew System::Windows::Forms::GroupBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->checkBox_Hotkeys = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox_LogEntityLabels = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_MuteConsole = (gcnew System::Windows::Forms::CheckBox());
			this->button_AddIgnoredEntity = (gcnew System::Windows::Forms::Button());
			this->textBox_IgnoreEntity = (gcnew System::Windows::Forms::TextBox());
			this->checkBox_LogEntity = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox_FollowMovementSkill = (gcnew System::Windows::Forms::ComboBox());
			this->checkBox_Follow = (gcnew System::Windows::Forms::CheckBox());
			this->textBox_FollowCharName = (gcnew System::Windows::Forms::TextBox());
			this->groupBox_Entities = (gcnew System::Windows::Forms::GroupBox());
			this->label_PlayerClass = (gcnew System::Windows::Forms::Label());
			this->label_Exp = (gcnew System::Windows::Forms::Label());
			this->label_Level = (gcnew System::Windows::Forms::Label());
			this->label_Status = (gcnew System::Windows::Forms::Label());
			this->label_GridY = (gcnew System::Windows::Forms::Label());
			this->checkBox_DisplayPlayerData = (gcnew System::Windows::Forms::CheckBox());
			this->label_GridX = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label_PlayerES = (gcnew System::Windows::Forms::Label());
			this->label_MP = (gcnew System::Windows::Forms::Label());
			this->label_HP = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown_CPUReducerTime = (gcnew System::Windows::Forms::NumericUpDown());
			this->checkBox_StopRender = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_ReduceCPU = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_RAMReduce = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox_Utilities = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox_LogHoveredElements = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_NullTerrain = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_HookClientMsg = (gcnew System::Windows::Forms::CheckBox());
			this->button_RevealMap = (gcnew System::Windows::Forms::Button());
			this->tabPage_LUA = (gcnew System::Windows::Forms::TabPage());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox_RepeatScript = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_RandomizingLUAName = (gcnew System::Windows::Forms::CheckBox());
			this->textBox_ScriptText = (gcnew System::Windows::Forms::TextBox());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage_TradeBot = (gcnew System::Windows::Forms::TabPage());
			this->groupBox13 = (gcnew System::Windows::Forms::GroupBox());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
			this->groupBox12 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox_AutoSellEverything = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_LogAutoTradeData = (gcnew System::Windows::Forms::CheckBox());
			this->comboBox_AutoTradeServer = (gcnew System::Windows::Forms::ComboBox());
			this->textBox_AutoBuyItemName = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->comboBox_WTBExchangeItem = (gcnew System::Windows::Forms::ComboBox());
			this->numericUpDown_AutoBuyExchangeQuantity = (gcnew System::Windows::Forms::NumericUpDown());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown_WTBQuantity = (gcnew System::Windows::Forms::NumericUpDown());
			this->radioButton_AutoSell = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton_AutoBuy = (gcnew System::Windows::Forms::RadioButton());
			this->checkBox_TradeBot = (gcnew System::Windows::Forms::CheckBox());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->contextMenuStrip_Packets->SuspendLayout();
			this->menuStrip_MainMenu->SuspendLayout();
			this->tabPage_Bot->SuspendLayout();
			this->groupBox15->SuspendLayout();
			this->groupBox9->SuspendLayout();
			this->groupBox11->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			this->groupBox8->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_FlaskES))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_FlaskMP))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_FlaskHP))->BeginInit();
			this->tabPage_Packets->SuspendLayout();
			this->groupBox17->SuspendLayout();
			this->groupBox16->SuspendLayout();
			this->tabPage_Hacks->SuspendLayout();
			this->groupBox14->SuspendLayout();
			this->groupBox10->SuspendLayout();
			this->groupBox7->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->groupBox_Entities->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_CPUReducerTime))->BeginInit();
			this->groupBox_Utilities->SuspendLayout();
			this->tabPage_LUA->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage_TradeBot->SuspendLayout();
			this->groupBox13->SuspendLayout();
			this->groupBox12->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_AutoBuyExchangeQuantity))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_WTBQuantity))->BeginInit();
			this->SuspendLayout();
			// 
			// contextMenuStrip_Packets
			// 
			this->contextMenuStrip_Packets->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->copyToolStripMenuItem,
					this->clearAllToolStripMenuItem, this->blockOpcodeToolStripMenuItem, this->ignoreOpcodeToolStripMenuItem
			});
			this->contextMenuStrip_Packets->Name = L"contextMenuStrip_Packets";
			this->contextMenuStrip_Packets->Size = System::Drawing::Size(154, 92);
			// 
			// copyToolStripMenuItem
			// 
			this->copyToolStripMenuItem->Name = L"copyToolStripMenuItem";
			this->copyToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->copyToolStripMenuItem->Text = L"Copy";
			this->copyToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::copyToolStripMenuItem_Click);
			// 
			// clearAllToolStripMenuItem
			// 
			this->clearAllToolStripMenuItem->Name = L"clearAllToolStripMenuItem";
			this->clearAllToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->clearAllToolStripMenuItem->Text = L"Clear All";
			this->clearAllToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::clearAllToolStripMenuItem_Click);
			// 
			// blockOpcodeToolStripMenuItem
			// 
			this->blockOpcodeToolStripMenuItem->Name = L"blockOpcodeToolStripMenuItem";
			this->blockOpcodeToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->blockOpcodeToolStripMenuItem->Text = L"Block Opcode";
			// 
			// ignoreOpcodeToolStripMenuItem
			// 
			this->ignoreOpcodeToolStripMenuItem->Name = L"ignoreOpcodeToolStripMenuItem";
			this->ignoreOpcodeToolStripMenuItem->Size = System::Drawing::Size(153, 22);
			this->ignoreOpcodeToolStripMenuItem->Text = L"Ignore Opcode";
			// 
			// menuStrip_MainMenu
			// 
			this->menuStrip_MainMenu->BackColor = System::Drawing::SystemColors::Control;
			this->menuStrip_MainMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->fileToolStripMenuItem,
					this->scriptingToolStripMenuItem, this->bottingToolStripMenuItem, this->helpToolStripMenuItem
			});
			this->menuStrip_MainMenu->Location = System::Drawing::Point(0, 0);
			this->menuStrip_MainMenu->Name = L"menuStrip_MainMenu";
			this->menuStrip_MainMenu->Padding = System::Windows::Forms::Padding(6, 1, 0, 1);
			this->menuStrip_MainMenu->Size = System::Drawing::Size(669, 24);
			this->menuStrip_MainMenu->TabIndex = 1;
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->openToolStripMenuItem,
					this->saveToolStripMenuItem, this->saveAsToolStripMenuItem, this->languagesToolStripMenuItem, this->shutdownToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 22);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(131, 22);
			this->openToolStripMenuItem->Text = L"Open";
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(131, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(131, 22);
			this->saveAsToolStripMenuItem->Text = L"Save As...";
			// 
			// languagesToolStripMenuItem
			// 
			this->languagesToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->chineseCNToolStripMenuItem,
					this->englishENToolStripMenuItem, this->russianRUToolStripMenuItem
			});
			this->languagesToolStripMenuItem->Name = L"languagesToolStripMenuItem";
			this->languagesToolStripMenuItem->Size = System::Drawing::Size(131, 22);
			this->languagesToolStripMenuItem->Text = L"Languages";
			// 
			// chineseCNToolStripMenuItem
			// 
			this->chineseCNToolStripMenuItem->Name = L"chineseCNToolStripMenuItem";
			this->chineseCNToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->chineseCNToolStripMenuItem->Text = L"中文 (CN)";
			this->chineseCNToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::chineseCNToolStripMenuItem_Click);
			// 
			// englishENToolStripMenuItem
			// 
			this->englishENToolStripMenuItem->Name = L"englishENToolStripMenuItem";
			this->englishENToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->englishENToolStripMenuItem->Text = L"English (EN)";
			this->englishENToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::englishENToolStripMenuItem_Click);
			// 
			// russianRUToolStripMenuItem
			// 
			this->russianRUToolStripMenuItem->Name = L"russianRUToolStripMenuItem";
			this->russianRUToolStripMenuItem->Size = System::Drawing::Size(140, 22);
			this->russianRUToolStripMenuItem->Text = L"Russian (RU)";
			this->russianRUToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::russianRUToolStripMenuItem_Click);
			// 
			// shutdownToolStripMenuItem
			// 
			this->shutdownToolStripMenuItem->Name = L"shutdownToolStripMenuItem";
			this->shutdownToolStripMenuItem->Size = System::Drawing::Size(131, 22);
			this->shutdownToolStripMenuItem->Text = L"Shutdown";
			// 
			// scriptingToolStripMenuItem
			// 
			this->scriptingToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->functionsToolStripMenuItem,
					this->saveAsToolStripMenuItem1, this->saveToolStripMenuItem1, this->runToolStripMenuItem
			});
			this->scriptingToolStripMenuItem->Name = L"scriptingToolStripMenuItem";
			this->scriptingToolStripMenuItem->Size = System::Drawing::Size(66, 22);
			this->scriptingToolStripMenuItem->Text = L"Scripting";
			// 
			// functionsToolStripMenuItem
			// 
			this->functionsToolStripMenuItem->Name = L"functionsToolStripMenuItem";
			this->functionsToolStripMenuItem->Size = System::Drawing::Size(126, 22);
			this->functionsToolStripMenuItem->Text = L"Functions";
			// 
			// saveAsToolStripMenuItem1
			// 
			this->saveAsToolStripMenuItem1->Name = L"saveAsToolStripMenuItem1";
			this->saveAsToolStripMenuItem1->Size = System::Drawing::Size(126, 22);
			this->saveAsToolStripMenuItem1->Text = L"Save As...";
			// 
			// saveToolStripMenuItem1
			// 
			this->saveToolStripMenuItem1->Name = L"saveToolStripMenuItem1";
			this->saveToolStripMenuItem1->Size = System::Drawing::Size(126, 22);
			this->saveToolStripMenuItem1->Text = L"Save";
			// 
			// runToolStripMenuItem
			// 
			this->runToolStripMenuItem->Name = L"runToolStripMenuItem";
			this->runToolStripMenuItem->Size = System::Drawing::Size(126, 22);
			this->runToolStripMenuItem->Text = L"Run";
			// 
			// bottingToolStripMenuItem
			// 
			this->bottingToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->loadProfileToolStripMenuItem,
					this->saveProfileAsToolStripMenuItem
			});
			this->bottingToolStripMenuItem->Name = L"bottingToolStripMenuItem";
			this->bottingToolStripMenuItem->Size = System::Drawing::Size(58, 22);
			this->bottingToolStripMenuItem->Text = L"Botting";
			// 
			// loadProfileToolStripMenuItem
			// 
			this->loadProfileToolStripMenuItem->Name = L"loadProfileToolStripMenuItem";
			this->loadProfileToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->loadProfileToolStripMenuItem->Text = L"Load Profile";
			this->loadProfileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::loadProfileToolStripMenuItem_Click);
			// 
			// saveProfileAsToolStripMenuItem
			// 
			this->saveProfileAsToolStripMenuItem->Name = L"saveProfileAsToolStripMenuItem";
			this->saveProfileAsToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->saveProfileAsToolStripMenuItem->Text = L"Save Profile As...";
			this->saveProfileAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveProfileAsToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->updateCheckToolStripMenuItem,
					this->hotkeysToolStripMenuItem, this->instructionsToolStripMenuItem, this->creditsToolStripMenuItem, this->donateToolStripMenuItem,
					this->fineprintToolStripMenuItem
			});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 22);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// updateCheckToolStripMenuItem
			// 
			this->updateCheckToolStripMenuItem->Name = L"updateCheckToolStripMenuItem";
			this->updateCheckToolStripMenuItem->Size = System::Drawing::Size(235, 22);
			this->updateCheckToolStripMenuItem->Text = L"Check For Updates";
			this->updateCheckToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::updateCheckToolStripMenuItem_Click);
			// 
			// hotkeysToolStripMenuItem
			// 
			this->hotkeysToolStripMenuItem->Name = L"hotkeysToolStripMenuItem";
			this->hotkeysToolStripMenuItem->Size = System::Drawing::Size(235, 22);
			this->hotkeysToolStripMenuItem->Text = L"Hotkeys";
			this->hotkeysToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::hotkeysToolStripMenuItem_Click);
			// 
			// instructionsToolStripMenuItem
			// 
			this->instructionsToolStripMenuItem->Name = L"instructionsToolStripMenuItem";
			this->instructionsToolStripMenuItem->Size = System::Drawing::Size(235, 22);
			this->instructionsToolStripMenuItem->Text = L"Manual";
			// 
			// creditsToolStripMenuItem
			// 
			this->creditsToolStripMenuItem->Name = L"creditsToolStripMenuItem";
			this->creditsToolStripMenuItem->Size = System::Drawing::Size(235, 22);
			this->creditsToolStripMenuItem->Text = L"Credits";
			this->creditsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::creditsToolStripMenuItem_Click);
			// 
			// donateToolStripMenuItem
			// 
			this->donateToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->bitcoinToolStripMenuItem,
					this->ethereumToolStripMenuItem, this->payPalToolStripMenuItem
			});
			this->donateToolStripMenuItem->Name = L"donateToolStripMenuItem";
			this->donateToolStripMenuItem->Size = System::Drawing::Size(235, 22);
			this->donateToolStripMenuItem->Text = L"Become an Investor/Supporter";
			// 
			// bitcoinToolStripMenuItem
			// 
			this->bitcoinToolStripMenuItem->Name = L"bitcoinToolStripMenuItem";
			this->bitcoinToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->bitcoinToolStripMenuItem->Text = L"Bitcoin";
			this->bitcoinToolStripMenuItem->ToolTipText = L"Bitcoin Donations";
			this->bitcoinToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::bitcoinToolStripMenuItem_Click);
			// 
			// ethereumToolStripMenuItem
			// 
			this->ethereumToolStripMenuItem->Name = L"ethereumToolStripMenuItem";
			this->ethereumToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->ethereumToolStripMenuItem->Text = L"Ethereum";
			this->ethereumToolStripMenuItem->ToolTipText = L"Ether Donations";
			this->ethereumToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ethereumToolStripMenuItem_Click);
			// 
			// payPalToolStripMenuItem
			// 
			this->payPalToolStripMenuItem->Enabled = false;
			this->payPalToolStripMenuItem->Name = L"payPalToolStripMenuItem";
			this->payPalToolStripMenuItem->Size = System::Drawing::Size(125, 22);
			this->payPalToolStripMenuItem->Text = L"PayPal";
			this->payPalToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::payPalToolStripMenuItem_Click);
			// 
			// fineprintToolStripMenuItem
			// 
			this->fineprintToolStripMenuItem->Name = L"fineprintToolStripMenuItem";
			this->fineprintToolStripMenuItem->Size = System::Drawing::Size(235, 22);
			this->fineprintToolStripMenuItem->Text = L"Fine-print (*)";
			this->fineprintToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::fineprintToolStripMenuItem_Click);
			// 
			// toolTip_Run
			// 
			this->toolTip_Run->ToolTipTitle = L"Executes the text above as LUA";
			// 
			// button_RunLUA
			// 
			this->button_RunLUA->BackColor = System::Drawing::Color::Transparent;
			this->button_RunLUA->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_RunLUA.BackgroundImage")));
			this->button_RunLUA->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_RunLUA->Location = System::Drawing::Point(10, 20);
			this->button_RunLUA->Name = L"button_RunLUA";
			this->button_RunLUA->Size = System::Drawing::Size(52, 46);
			this->button_RunLUA->TabIndex = 14;
			this->toolTip_Run->SetToolTip(this->button_RunLUA, L"Execute Script");
			this->button_RunLUA->UseVisualStyleBackColor = false;
			this->button_RunLUA->Click += gcnew System::EventHandler(this, &MainForm::button1_Click_1);
			// 
			// toolTip_Stop
			// 
			this->toolTip_Stop->ToolTipTitle = L"Stops the current running script.";
			// 
			// button_StopLUA
			// 
			this->button_StopLUA->BackColor = System::Drawing::Color::Transparent;
			this->button_StopLUA->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_StopLUA.BackgroundImage")));
			this->button_StopLUA->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_StopLUA->Location = System::Drawing::Point(74, 20);
			this->button_StopLUA->Name = L"button_StopLUA";
			this->button_StopLUA->Size = System::Drawing::Size(50, 46);
			this->button_StopLUA->TabIndex = 15;
			this->toolTip_Stop->SetToolTip(this->button_StopLUA, L"Stop Script");
			this->button_StopLUA->UseVisualStyleBackColor = false;
			this->button_StopLUA->Click += gcnew System::EventHandler(this, &MainForm::button_StopLUA_Click);
			// 
			// toolTip_SaveScript
			// 
			this->toolTip_SaveScript->ToolTipTitle = L"Saves the above as a LUA file.";
			// 
			// button_SaveLUA
			// 
			this->button_SaveLUA->BackColor = System::Drawing::Color::Transparent;
			this->button_SaveLUA->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_SaveLUA.BackgroundImage")));
			this->button_SaveLUA->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_SaveLUA->Location = System::Drawing::Point(137, 20);
			this->button_SaveLUA->Name = L"button_SaveLUA";
			this->button_SaveLUA->Size = System::Drawing::Size(53, 46);
			this->button_SaveLUA->TabIndex = 16;
			this->toolTip_SaveScript->SetToolTip(this->button_SaveLUA, L"Save Script");
			this->button_SaveLUA->UseVisualStyleBackColor = false;
			this->button_SaveLUA->Click += gcnew System::EventHandler(this, &MainForm::button_SaveLUA_Click);
			// 
			// toolTip_LoadScript
			// 
			this->toolTip_LoadScript->ToolTipTitle = L"Loads a file into the text control above.";
			// 
			// button_LoadLUA
			// 
			this->button_LoadLUA->BackColor = System::Drawing::Color::Transparent;
			this->button_LoadLUA->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_LoadLUA.BackgroundImage")));
			this->button_LoadLUA->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_LoadLUA->Location = System::Drawing::Point(201, 20);
			this->button_LoadLUA->Name = L"button_LoadLUA";
			this->button_LoadLUA->Size = System::Drawing::Size(50, 46);
			this->button_LoadLUA->TabIndex = 17;
			this->toolTip_LoadScript->SetToolTip(this->button_LoadLUA, L"Load Script");
			this->button_LoadLUA->UseVisualStyleBackColor = false;
			this->button_LoadLUA->Click += gcnew System::EventHandler(this, &MainForm::button_LoadLUA_Click);
			// 
			// toolTip_Download
			// 
			this->toolTip_Download->ToolTipTitle = L"Download Script";
			// 
			// button_DownloadLUA
			// 
			this->button_DownloadLUA->BackColor = System::Drawing::Color::Transparent;
			this->button_DownloadLUA->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button_DownloadLUA.BackgroundImage")));
			this->button_DownloadLUA->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button_DownloadLUA->Enabled = false;
			this->button_DownloadLUA->Location = System::Drawing::Point(263, 19);
			this->button_DownloadLUA->Name = L"button_DownloadLUA";
			this->button_DownloadLUA->Size = System::Drawing::Size(52, 47);
			this->button_DownloadLUA->TabIndex = 18;
			this->toolTip_Download->SetToolTip(this->button_DownloadLUA, L"Download Script");
			this->button_DownloadLUA->UseVisualStyleBackColor = false;
			this->button_DownloadLUA->Click += gcnew System::EventHandler(this, &MainForm::button_DownloadLUA_Click);
			// 
			// openFileDialog_OutputLogFile
			// 
			this->openFileDialog_OutputLogFile->FileName = L"okpoe_output.txt";
			// 
			// tabPage_Bot
			// 
			this->tabPage_Bot->BackColor = System::Drawing::Color::Transparent;
			this->tabPage_Bot->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->tabPage_Bot->Controls->Add(this->checkBox_TrialHelper);
			this->tabPage_Bot->Controls->Add(this->groupBox15);
			this->tabPage_Bot->Controls->Add(this->groupBox9);
			this->tabPage_Bot->Controls->Add(this->groupBox11);
			this->tabPage_Bot->Controls->Add(this->groupBox8);
			this->tabPage_Bot->Controls->Add(this->groupBox5);
			this->tabPage_Bot->Controls->Add(this->groupBox4);
			this->tabPage_Bot->Controls->Add(this->groupBox2);
			this->tabPage_Bot->Location = System::Drawing::Point(4, 22);
			this->tabPage_Bot->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->tabPage_Bot->Name = L"tabPage_Bot";
			this->tabPage_Bot->Size = System::Drawing::Size(642, 486);
			this->tabPage_Bot->TabIndex = 2;
			this->tabPage_Bot->Text = L"Bots";
			// 
			// checkBox_TrialHelper
			// 
			this->checkBox_TrialHelper->AutoSize = true;
			this->checkBox_TrialHelper->Location = System::Drawing::Point(20, 330);
			this->checkBox_TrialHelper->Name = L"checkBox_TrialHelper";
			this->checkBox_TrialHelper->Size = System::Drawing::Size(117, 17);
			this->checkBox_TrialHelper->TabIndex = 15;
			this->checkBox_TrialHelper->Text = L"[BETA] Trial Helper";
			this->checkBox_TrialHelper->UseVisualStyleBackColor = true;
			this->checkBox_TrialHelper->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_TrialHelper_CheckedChanged);
			// 
			// groupBox15
			// 
			this->groupBox15->Controls->Add(this->button_PlayBackMovements);
			this->groupBox15->Controls->Add(this->checkBox_RecordMovement);
			this->groupBox15->Location = System::Drawing::Point(317, 394);
			this->groupBox15->Name = L"groupBox15";
			this->groupBox15->Size = System::Drawing::Size(198, 74);
			this->groupBox15->TabIndex = 14;
			this->groupBox15->TabStop = false;
			this->groupBox15->Text = L"Monitoring";
			// 
			// button_PlayBackMovements
			// 
			this->button_PlayBackMovements->Location = System::Drawing::Point(6, 43);
			this->button_PlayBackMovements->Name = L"button_PlayBackMovements";
			this->button_PlayBackMovements->Size = System::Drawing::Size(186, 23);
			this->button_PlayBackMovements->TabIndex = 1;
			this->button_PlayBackMovements->Text = L"Play-back Movements";
			this->button_PlayBackMovements->UseVisualStyleBackColor = true;
			this->button_PlayBackMovements->Click += gcnew System::EventHandler(this, &MainForm::button_PlayBackMovements_Click);
			// 
			// checkBox_RecordMovement
			// 
			this->checkBox_RecordMovement->AutoSize = true;
			this->checkBox_RecordMovement->Location = System::Drawing::Point(6, 21);
			this->checkBox_RecordMovement->Name = L"checkBox_RecordMovement";
			this->checkBox_RecordMovement->Size = System::Drawing::Size(153, 17);
			this->checkBox_RecordMovement->TabIndex = 0;
			this->checkBox_RecordMovement->Text = L"Record Movement Vectors";
			this->checkBox_RecordMovement->UseVisualStyleBackColor = true;
			this->checkBox_RecordMovement->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_RecordMovement_CheckedChanged);
			// 
			// groupBox9
			// 
			this->groupBox9->Controls->Add(this->button_UnloadDLL);
			this->groupBox9->Controls->Add(this->checkBox_DebugMode);
			this->groupBox9->Location = System::Drawing::Point(521, 400);
			this->groupBox9->Name = L"groupBox9";
			this->groupBox9->Size = System::Drawing::Size(109, 81);
			this->groupBox9->TabIndex = 13;
			this->groupBox9->TabStop = false;
			this->groupBox9->Text = L"DEBUG";
			// 
			// button_UnloadDLL
			// 
			this->button_UnloadDLL->Location = System::Drawing::Point(6, 46);
			this->button_UnloadDLL->Name = L"button_UnloadDLL";
			this->button_UnloadDLL->Size = System::Drawing::Size(75, 23);
			this->button_UnloadDLL->TabIndex = 12;
			this->button_UnloadDLL->Text = L"Unload DLL";
			this->button_UnloadDLL->UseVisualStyleBackColor = true;
			this->button_UnloadDLL->Click += gcnew System::EventHandler(this, &MainForm::button_UnloadDLL_Click);
			// 
			// checkBox_DebugMode
			// 
			this->checkBox_DebugMode->AutoSize = true;
			this->checkBox_DebugMode->Location = System::Drawing::Point(6, 21);
			this->checkBox_DebugMode->Name = L"checkBox_DebugMode";
			this->checkBox_DebugMode->Size = System::Drawing::Size(88, 17);
			this->checkBox_DebugMode->TabIndex = 11;
			this->checkBox_DebugMode->Text = L"Debug Mode";
			this->checkBox_DebugMode->UseVisualStyleBackColor = true;
			this->checkBox_DebugMode->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_DebugMode_CheckedChanged);
			// 
			// groupBox11
			// 
			this->groupBox11->BackColor = System::Drawing::Color::Transparent;
			this->groupBox11->Controls->Add(this->checkBox_Relogin);
			this->groupBox11->Controls->Add(this->label9);
			this->groupBox11->Controls->Add(this->numericUpDown1);
			this->groupBox11->ForeColor = System::Drawing::Color::Black;
			this->groupBox11->Location = System::Drawing::Point(371, 290);
			this->groupBox11->Name = L"groupBox11";
			this->groupBox11->Size = System::Drawing::Size(259, 63);
			this->groupBox11->TabIndex = 9;
			this->groupBox11->TabStop = false;
			this->groupBox11->Text = L"Re-Login On Disconnect (Under Construction!)";
			// 
			// checkBox_Relogin
			// 
			this->checkBox_Relogin->AutoSize = true;
			this->checkBox_Relogin->Location = System::Drawing::Point(10, 40);
			this->checkBox_Relogin->Name = L"checkBox_Relogin";
			this->checkBox_Relogin->Size = System::Drawing::Size(59, 17);
			this->checkBox_Relogin->TabIndex = 2;
			this->checkBox_Relogin->Text = L"Enable";
			this->checkBox_Relogin->UseVisualStyleBackColor = true;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(6, 21);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(108, 13);
			this->label9->TabIndex = 1;
			this->label9->Text = L"Character Slot In List:";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(125, 19);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(128, 20);
			this->numericUpDown1->TabIndex = 0;
			// 
			// groupBox8
			// 
			this->groupBox8->BackColor = System::Drawing::Color::Transparent;
			this->groupBox8->Controls->Add(this->checkBox_LevelSkillGems);
			this->groupBox8->Controls->Add(this->radioButton_ReviveCheckpoint);
			this->groupBox8->Controls->Add(this->radioButton_ReviveTown);
			this->groupBox8->Controls->Add(this->checkBox_AutoRevive);
			this->groupBox8->Controls->Add(this->checkBox_EnterAreaTransitions);
			this->groupBox8->ForeColor = System::Drawing::Color::Black;
			this->groupBox8->Location = System::Drawing::Point(330, 164);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Size = System::Drawing::Size(300, 115);
			this->groupBox8->TabIndex = 6;
			this->groupBox8->TabStop = false;
			this->groupBox8->Text = L"Misc.";
			// 
			// checkBox_LevelSkillGems
			// 
			this->checkBox_LevelSkillGems->AutoSize = true;
			this->checkBox_LevelSkillGems->Location = System::Drawing::Point(10, 89);
			this->checkBox_LevelSkillGems->Name = L"checkBox_LevelSkillGems";
			this->checkBox_LevelSkillGems->Size = System::Drawing::Size(125, 17);
			this->checkBox_LevelSkillGems->TabIndex = 10;
			this->checkBox_LevelSkillGems->Text = L"Auto-level Skill Gems";
			this->checkBox_LevelSkillGems->UseVisualStyleBackColor = true;
			this->checkBox_LevelSkillGems->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_LevelSkillGems_CheckedChanged);
			// 
			// radioButton_ReviveCheckpoint
			// 
			this->radioButton_ReviveCheckpoint->AutoSize = true;
			this->radioButton_ReviveCheckpoint->Checked = true;
			this->radioButton_ReviveCheckpoint->Location = System::Drawing::Point(83, 62);
			this->radioButton_ReviveCheckpoint->Name = L"radioButton_ReviveCheckpoint";
			this->radioButton_ReviveCheckpoint->Size = System::Drawing::Size(79, 17);
			this->radioButton_ReviveCheckpoint->TabIndex = 5;
			this->radioButton_ReviveCheckpoint->TabStop = true;
			this->radioButton_ReviveCheckpoint->Text = L"Checkpoint";
			this->radioButton_ReviveCheckpoint->UseVisualStyleBackColor = true;
			// 
			// radioButton_ReviveTown
			// 
			this->radioButton_ReviveTown->AutoSize = true;
			this->radioButton_ReviveTown->Location = System::Drawing::Point(25, 63);
			this->radioButton_ReviveTown->Name = L"radioButton_ReviveTown";
			this->radioButton_ReviveTown->Size = System::Drawing::Size(52, 17);
			this->radioButton_ReviveTown->TabIndex = 4;
			this->radioButton_ReviveTown->Text = L"Town";
			this->radioButton_ReviveTown->UseVisualStyleBackColor = true;
			// 
			// checkBox_AutoRevive
			// 
			this->checkBox_AutoRevive->AutoSize = true;
			this->checkBox_AutoRevive->Checked = true;
			this->checkBox_AutoRevive->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox_AutoRevive->Location = System::Drawing::Point(12, 42);
			this->checkBox_AutoRevive->Name = L"checkBox_AutoRevive";
			this->checkBox_AutoRevive->Size = System::Drawing::Size(85, 17);
			this->checkBox_AutoRevive->TabIndex = 3;
			this->checkBox_AutoRevive->Text = L"Auto Revive";
			this->checkBox_AutoRevive->UseVisualStyleBackColor = true;
			this->checkBox_AutoRevive->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_AutoRevive_CheckedChanged);
			// 
			// checkBox_EnterAreaTransitions
			// 
			this->checkBox_EnterAreaTransitions->AutoSize = true;
			this->checkBox_EnterAreaTransitions->Location = System::Drawing::Point(12, 20);
			this->checkBox_EnterAreaTransitions->Name = L"checkBox_EnterAreaTransitions";
			this->checkBox_EnterAreaTransitions->Size = System::Drawing::Size(195, 17);
			this->checkBox_EnterAreaTransitions->TabIndex = 0;
			this->checkBox_EnterAreaTransitions->Text = L"Enter Area Transitions Automatically";
			this->checkBox_EnterAreaTransitions->UseVisualStyleBackColor = true;
			this->checkBox_EnterAreaTransitions->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_EnterAreaTransitions_CheckedChanged);
			// 
			// groupBox5
			// 
			this->groupBox5->BackColor = System::Drawing::Color::Transparent;
			this->groupBox5->Controls->Add(this->label17);
			this->groupBox5->Controls->Add(this->comboBox2);
			this->groupBox5->Controls->Add(this->checkBox_IsRangedSkill);
			this->groupBox5->Controls->Add(this->checkBox_RighteousFire);
			this->groupBox5->Controls->Add(this->checkBox_UsingTotems);
			this->groupBox5->Controls->Add(this->comboBox1);
			this->groupBox5->Controls->Add(this->label12);
			this->groupBox5->Controls->Add(this->label10);
			this->groupBox5->Controls->Add(this->comboBox_PortalGemSlot);
			this->groupBox5->Controls->Add(this->checkBox_VaalSkill);
			this->groupBox5->Controls->Add(this->label7);
			this->groupBox5->Controls->Add(this->comboBox_MovementSkill);
			this->groupBox5->Controls->Add(this->checkBox_IsSkillMelee);
			this->groupBox5->Controls->Add(this->comboBox_SkillGemSlot);
			this->groupBox5->Controls->Add(this->label6);
			this->groupBox5->Controls->Add(this->checkBox_IsTargeting);
			this->groupBox5->ForeColor = System::Drawing::Color::Black;
			this->groupBox5->Location = System::Drawing::Point(14, 7);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(268, 301);
			this->groupBox5->TabIndex = 5;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Fighting";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(5, 43);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(131, 13);
			this->label17->TabIndex = 26;
			this->label17->Text = L"Secondary Attacking Skill:";
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(30) {
				L"Helmet 1", L"Helmet 2", L"Helmet 3", L"Helmet 4",
					L"Body 1", L"Body 2", L"Body 3", L"Body 4", L"Body 5", L"Body 6", L"Gloves 1", L"Gloves 2", L"Gloves 3", L"Gloves 4", L"Boots 1",
					L"Boots 2", L"Boots 3", L"Boots 4", L"LeftHand 1", L"LeftHand 2", L"LeftHand 3", L"RightHand 1", L"RightHand 2", L"RightHand 3",
					L"Weapon 1", L"Weapon 2", L"Weapon 3", L"Weapon 4", L"Weapon 5", L"Weapon 6"
			});
			this->comboBox2->Location = System::Drawing::Point(141, 40);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(112, 21);
			this->comboBox2->TabIndex = 25;
			this->comboBox2->Text = L"Skill Gem Slot";
			// 
			// checkBox_IsRangedSkill
			// 
			this->checkBox_IsRangedSkill->AutoSize = true;
			this->checkBox_IsRangedSkill->Location = System::Drawing::Point(138, 123);
			this->checkBox_IsRangedSkill->Name = L"checkBox_IsRangedSkill";
			this->checkBox_IsRangedSkill->Size = System::Drawing::Size(115, 17);
			this->checkBox_IsRangedSkill->TabIndex = 24;
			this->checkBox_IsRangedSkill->Text = L"Far Range Attacks";
			this->checkBox_IsRangedSkill->UseVisualStyleBackColor = true;
			this->checkBox_IsRangedSkill->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_IsRangedSkill_CheckedChanged);
			// 
			// checkBox_RighteousFire
			// 
			this->checkBox_RighteousFire->AutoSize = true;
			this->checkBox_RighteousFire->Location = System::Drawing::Point(9, 146);
			this->checkBox_RighteousFire->Name = L"checkBox_RighteousFire";
			this->checkBox_RighteousFire->Size = System::Drawing::Size(94, 17);
			this->checkBox_RighteousFire->TabIndex = 23;
			this->checkBox_RighteousFire->Text = L"Righteous Fire";
			this->checkBox_RighteousFire->UseVisualStyleBackColor = true;
			this->checkBox_RighteousFire->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_RighteousFire_CheckedChanged);
			// 
			// checkBox_UsingTotems
			// 
			this->checkBox_UsingTotems->AutoSize = true;
			this->checkBox_UsingTotems->Location = System::Drawing::Point(9, 169);
			this->checkBox_UsingTotems->Name = L"checkBox_UsingTotems";
			this->checkBox_UsingTotems->Size = System::Drawing::Size(91, 17);
			this->checkBox_UsingTotems->TabIndex = 12;
			this->checkBox_UsingTotems->Text = L"Using Totems";
			this->checkBox_UsingTotems->UseVisualStyleBackColor = true;
			this->checkBox_UsingTotems->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_UsingTotems_CheckedChanged);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(31) {
				L"Helmet 1", L"Helmet 2", L"Helmet 3", L"Helmet 4",
					L"Body 1", L"Body 2", L"Body 3", L"Body 4", L"Body 5", L"Body 6", L"Gloves 1", L"Gloves 2", L"Gloves 3", L"Gloves 4", L"Boots 1",
					L"Boots 2", L"Boots 3", L"Boots 4", L"LeftHand 1", L"LeftHand 2", L"LeftHand 3", L"RightHand 1", L"RightHand 2", L"RightHand 3",
					L"Weapon 1", L"Weapon 2", L"Weapon 3", L"Weapon 4", L"Weapon 5", L"Weapon 6", L"Run"
			});
			this->comboBox1->Location = System::Drawing::Point(148, 266);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(105, 21);
			this->comboBox1->TabIndex = 20;
			this->comboBox1->Text = L"Skill Gem Slot";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(9, 270);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(61, 13);
			this->label12->TabIndex = 19;
			this->label12->Text = L"Guard Skill:";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(7, 220);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(59, 13);
			this->label10->TabIndex = 18;
			this->label10->Text = L"Portal Skill:";
			// 
			// comboBox_PortalGemSlot
			// 
			this->comboBox_PortalGemSlot->FormattingEnabled = true;
			this->comboBox_PortalGemSlot->Items->AddRange(gcnew cli::array< System::Object^  >(31) {
				L"Helmet 1", L"Helmet 2", L"Helmet 3",
					L"Helmet 4", L"Body 1", L"Body 2", L"Body 3", L"Body 4", L"Body 5", L"Body 6", L"Gloves 1", L"Gloves 2", L"Gloves 3", L"Gloves 4",
					L"Boots 1", L"Boots 2", L"Boots 3", L"Boots 4", L"LeftHand 1", L"LeftHand 2", L"LeftHand 3", L"RightHand 1", L"RightHand 2",
					L"RightHand 3", L"Weapon 1", L"Weapon 2", L"Weapon 3", L"Weapon 4", L"Weapon 5", L"Weapon 6", L"Run"
			});
			this->comboBox_PortalGemSlot->Location = System::Drawing::Point(148, 216);
			this->comboBox_PortalGemSlot->Name = L"comboBox_PortalGemSlot";
			this->comboBox_PortalGemSlot->Size = System::Drawing::Size(105, 21);
			this->comboBox_PortalGemSlot->TabIndex = 17;
			this->comboBox_PortalGemSlot->Text = L"Skill Gem Slot";
			this->comboBox_PortalGemSlot->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBox_PortalGemSlot_SelectedIndexChanged);
			// 
			// checkBox_VaalSkill
			// 
			this->checkBox_VaalSkill->AutoSize = true;
			this->checkBox_VaalSkill->Location = System::Drawing::Point(138, 146);
			this->checkBox_VaalSkill->Name = L"checkBox_VaalSkill";
			this->checkBox_VaalSkill->Size = System::Drawing::Size(79, 17);
			this->checkBox_VaalSkill->TabIndex = 16;
			this->checkBox_VaalSkill->Text = L"Skill is Vaal";
			this->checkBox_VaalSkill->UseVisualStyleBackColor = true;
			this->checkBox_VaalSkill->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_VaalSkill_CheckedChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(8, 245);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(82, 13);
			this->label7->TabIndex = 14;
			this->label7->Text = L"Movement Skill:";
			// 
			// comboBox_MovementSkill
			// 
			this->comboBox_MovementSkill->FormattingEnabled = true;
			this->comboBox_MovementSkill->Items->AddRange(gcnew cli::array< System::Object^  >(31) {
				L"Helmet 1", L"Helmet 2", L"Helmet 3",
					L"Helmet 4", L"Body 1", L"Body 2", L"Body 3", L"Body 4", L"Body 5", L"Body 6", L"Gloves 1", L"Gloves 2", L"Gloves 3", L"Gloves 4",
					L"Boots 1", L"Boots 2", L"Boots 3", L"Boots 4", L"LeftHand 1", L"LeftHand 2", L"LeftHand 3", L"RightHand 1", L"RightHand 2",
					L"RightHand 3", L"Weapon 1", L"Weapon 2", L"Weapon 3", L"Weapon 4", L"Weapon 5", L"Weapon 6", L"Run"
			});
			this->comboBox_MovementSkill->Location = System::Drawing::Point(148, 241);
			this->comboBox_MovementSkill->Name = L"comboBox_MovementSkill";
			this->comboBox_MovementSkill->Size = System::Drawing::Size(105, 21);
			this->comboBox_MovementSkill->TabIndex = 13;
			this->comboBox_MovementSkill->Text = L"Skill Gem Slot";
			this->comboBox_MovementSkill->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBox_MovementSkill_SelectedIndexChanged);
			// 
			// checkBox_IsSkillMelee
			// 
			this->checkBox_IsSkillMelee->AutoSize = true;
			this->checkBox_IsSkillMelee->Location = System::Drawing::Point(9, 123);
			this->checkBox_IsSkillMelee->Name = L"checkBox_IsSkillMelee";
			this->checkBox_IsSkillMelee->Size = System::Drawing::Size(77, 17);
			this->checkBox_IsSkillMelee->TabIndex = 7;
			this->checkBox_IsSkillMelee->Text = L"Melee Skill";
			this->checkBox_IsSkillMelee->UseVisualStyleBackColor = true;
			this->checkBox_IsSkillMelee->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_IsSkillMelee_CheckedChanged);
			// 
			// comboBox_SkillGemSlot
			// 
			this->comboBox_SkillGemSlot->FormattingEnabled = true;
			this->comboBox_SkillGemSlot->Items->AddRange(gcnew cli::array< System::Object^  >(30) {
				L"Helmet 1", L"Helmet 2", L"Helmet 3",
					L"Helmet 4", L"Body 1", L"Body 2", L"Body 3", L"Body 4", L"Body 5", L"Body 6", L"Gloves 1", L"Gloves 2", L"Gloves 3", L"Gloves 4",
					L"Boots 1", L"Boots 2", L"Boots 3", L"Boots 4", L"LeftHand 1", L"LeftHand 2", L"LeftHand 3", L"RightHand 1", L"RightHand 2",
					L"RightHand 3", L"Weapon 1", L"Weapon 2", L"Weapon 3", L"Weapon 4", L"Weapon 5", L"Weapon 6"
			});
			this->comboBox_SkillGemSlot->Location = System::Drawing::Point(141, 15);
			this->comboBox_SkillGemSlot->Name = L"comboBox_SkillGemSlot";
			this->comboBox_SkillGemSlot->Size = System::Drawing::Size(112, 21);
			this->comboBox_SkillGemSlot->TabIndex = 4;
			this->comboBox_SkillGemSlot->Text = L"Skill Gem Slot";
			this->comboBox_SkillGemSlot->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBox_SkillGemSlot_SelectedIndexChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(5, 20);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(103, 13);
			this->label6->TabIndex = 3;
			this->label6->Text = L"Main Attacking Skill:";
			// 
			// checkBox_IsTargeting
			// 
			this->checkBox_IsTargeting->AutoSize = true;
			this->checkBox_IsTargeting->Location = System::Drawing::Point(9, 71);
			this->checkBox_IsTargeting->Name = L"checkBox_IsTargeting";
			this->checkBox_IsTargeting->Size = System::Drawing::Size(107, 17);
			this->checkBox_IsTargeting->TabIndex = 0;
			this->checkBox_IsTargeting->Text = L"Enable Attacking";
			this->checkBox_IsTargeting->UseVisualStyleBackColor = true;
			this->checkBox_IsTargeting->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_IsTargeting_CheckedChanged);
			// 
			// groupBox4
			// 
			this->groupBox4->BackColor = System::Drawing::Color::Transparent;
			this->groupBox4->Controls->Add(this->button3);
			this->groupBox4->Controls->Add(this->textBox2);
			this->groupBox4->Controls->Add(this->radioButton_AutoLootUseBuiltin);
			this->groupBox4->Controls->Add(this->radioButton_AutoLootUseFile);
			this->groupBox4->Controls->Add(this->checkBox_AutoLoot);
			this->groupBox4->ForeColor = System::Drawing::Color::Black;
			this->groupBox4->Location = System::Drawing::Point(14, 359);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(259, 101);
			this->groupBox4->TabIndex = 4;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Loot Settings";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(178, 68);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 7;
			this->button3->Text = L"Ignore Item";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(11, 67);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(161, 20);
			this->textBox2->TabIndex = 6;
			// 
			// radioButton_AutoLootUseBuiltin
			// 
			this->radioButton_AutoLootUseBuiltin->AutoSize = true;
			this->radioButton_AutoLootUseBuiltin->Location = System::Drawing::Point(104, 42);
			this->radioButton_AutoLootUseBuiltin->Name = L"radioButton_AutoLootUseBuiltin";
			this->radioButton_AutoLootUseBuiltin->Size = System::Drawing::Size(120, 17);
			this->radioButton_AutoLootUseBuiltin->TabIndex = 5;
			this->radioButton_AutoLootUseBuiltin->TabStop = true;
			this->radioButton_AutoLootUseBuiltin->Text = L"Use Built-in Item List";
			this->radioButton_AutoLootUseBuiltin->UseVisualStyleBackColor = true;
			// 
			// radioButton_AutoLootUseFile
			// 
			this->radioButton_AutoLootUseFile->AutoSize = true;
			this->radioButton_AutoLootUseFile->Checked = true;
			this->radioButton_AutoLootUseFile->Location = System::Drawing::Point(10, 42);
			this->radioButton_AutoLootUseFile->Name = L"radioButton_AutoLootUseFile";
			this->radioButton_AutoLootUseFile->Size = System::Drawing::Size(81, 17);
			this->radioButton_AutoLootUseFile->TabIndex = 4;
			this->radioButton_AutoLootUseFile->TabStop = true;
			this->radioButton_AutoLootUseFile->Text = L"Use \'loot.ini\'";
			this->radioButton_AutoLootUseFile->UseVisualStyleBackColor = true;
			// 
			// checkBox_AutoLoot
			// 
			this->checkBox_AutoLoot->AutoSize = true;
			this->checkBox_AutoLoot->Location = System::Drawing::Point(11, 20);
			this->checkBox_AutoLoot->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox_AutoLoot->Name = L"checkBox_AutoLoot";
			this->checkBox_AutoLoot->Size = System::Drawing::Size(104, 17);
			this->checkBox_AutoLoot->TabIndex = 3;
			this->checkBox_AutoLoot->Text = L"Enable Auto-loot";
			this->checkBox_AutoLoot->UseVisualStyleBackColor = true;
			this->checkBox_AutoLoot->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_AutoLoot_CheckedChanged);
			// 
			// groupBox2
			// 
			this->groupBox2->BackColor = System::Drawing::Color::Transparent;
			this->groupBox2->Controls->Add(this->checkBox_AutoFlask50);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->numericUpDown_FlaskES);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Controls->Add(this->numericUpDown_FlaskMP);
			this->groupBox2->Controls->Add(this->checkBox_AutoFlask);
			this->groupBox2->Controls->Add(this->numericUpDown_FlaskHP);
			this->groupBox2->ForeColor = System::Drawing::Color::Black;
			this->groupBox2->Location = System::Drawing::Point(330, 7);
			this->groupBox2->Margin = System::Windows::Forms::Padding(1, 4, 1, 4);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(1, 4, 1, 4);
			this->groupBox2->Size = System::Drawing::Size(300, 150);
			this->groupBox2->TabIndex = 0;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Flasks";
			// 
			// checkBox_AutoFlask50
			// 
			this->checkBox_AutoFlask50->AutoSize = true;
			this->checkBox_AutoFlask50->Location = System::Drawing::Point(9, 109);
			this->checkBox_AutoFlask50->Name = L"checkBox_AutoFlask50";
			this->checkBox_AutoFlask50->Size = System::Drawing::Size(125, 17);
			this->checkBox_AutoFlask50->TabIndex = 8;
			this->checkBox_AutoFlask50->Text = L"Flask at 50% HP/MP";
			this->checkBox_AutoFlask50->UseVisualStyleBackColor = true;
			this->checkBox_AutoFlask50->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_AutoFlask50_CheckedChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(95, 70);
			this->label3->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(115, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Flask on Energy Shield";
			// 
			// numericUpDown_FlaskES
			// 
			this->numericUpDown_FlaskES->Location = System::Drawing::Point(6, 68);
			this->numericUpDown_FlaskES->Margin = System::Windows::Forms::Padding(1, 4, 1, 4);
			this->numericUpDown_FlaskES->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->numericUpDown_FlaskES->Name = L"numericUpDown_FlaskES";
			this->numericUpDown_FlaskES->Size = System::Drawing::Size(79, 20);
			this->numericUpDown_FlaskES->TabIndex = 5;
			this->numericUpDown_FlaskES->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(95, 48);
			this->label2->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(77, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Flask on Mana";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(95, 24);
			this->label1->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(65, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Flask on HP";
			// 
			// numericUpDown_FlaskMP
			// 
			this->numericUpDown_FlaskMP->Location = System::Drawing::Point(6, 44);
			this->numericUpDown_FlaskMP->Margin = System::Windows::Forms::Padding(1, 4, 1, 4);
			this->numericUpDown_FlaskMP->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->numericUpDown_FlaskMP->Name = L"numericUpDown_FlaskMP";
			this->numericUpDown_FlaskMP->Size = System::Drawing::Size(79, 20);
			this->numericUpDown_FlaskMP->TabIndex = 2;
			this->numericUpDown_FlaskMP->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 50, 0, 0, 0 });
			// 
			// checkBox_AutoFlask
			// 
			this->checkBox_AutoFlask->AutoSize = true;
			this->checkBox_AutoFlask->Location = System::Drawing::Point(9, 128);
			this->checkBox_AutoFlask->Margin = System::Windows::Forms::Padding(1, 4, 1, 4);
			this->checkBox_AutoFlask->Name = L"checkBox_AutoFlask";
			this->checkBox_AutoFlask->Size = System::Drawing::Size(112, 17);
			this->checkBox_AutoFlask->TabIndex = 0;
			this->checkBox_AutoFlask->Text = L"Enable Auto-Flask";
			this->checkBox_AutoFlask->UseVisualStyleBackColor = true;
			this->checkBox_AutoFlask->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_AutoFlask_CheckedChanged);
			// 
			// numericUpDown_FlaskHP
			// 
			this->numericUpDown_FlaskHP->Location = System::Drawing::Point(6, 20);
			this->numericUpDown_FlaskHP->Margin = System::Windows::Forms::Padding(1, 4, 1, 4);
			this->numericUpDown_FlaskHP->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->numericUpDown_FlaskHP->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown_FlaskHP->Name = L"numericUpDown_FlaskHP";
			this->numericUpDown_FlaskHP->Size = System::Drawing::Size(79, 20);
			this->numericUpDown_FlaskHP->TabIndex = 1;
			this->numericUpDown_FlaskHP->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2300, 0, 0, 0 });
			// 
			// tabPage_Packets
			// 
			this->tabPage_Packets->BackColor = System::Drawing::Color::Gainsboro;
			this->tabPage_Packets->Controls->Add(this->groupBox17);
			this->tabPage_Packets->Controls->Add(this->checkBox_LogRecv);
			this->tabPage_Packets->Controls->Add(this->button_SendPacket);
			this->tabPage_Packets->Controls->Add(this->textBox_SendPacketInput);
			this->tabPage_Packets->Controls->Add(this->checkBox_LogSP);
			this->tabPage_Packets->Controls->Add(this->listView_Packets);
			this->tabPage_Packets->Location = System::Drawing::Point(4, 22);
			this->tabPage_Packets->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->tabPage_Packets->Name = L"tabPage_Packets";
			this->tabPage_Packets->Padding = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->tabPage_Packets->Size = System::Drawing::Size(642, 486);
			this->tabPage_Packets->TabIndex = 1;
			this->tabPage_Packets->Text = L"Packets";
			// 
			// groupBox17
			// 
			this->groupBox17->Controls->Add(this->richTextBox_PacketPosition);
			this->groupBox17->Controls->Add(this->groupBox16);
			this->groupBox17->Controls->Add(this->richTextBox_PacketInspector);
			this->groupBox17->Controls->Add(this->richTextBox_PositionCounter);
			this->groupBox17->Location = System::Drawing::Point(638, 6);
			this->groupBox17->Name = L"groupBox17";
			this->groupBox17->Size = System::Drawing::Size(425, 475);
			this->groupBox17->TabIndex = 29;
			this->groupBox17->TabStop = false;
			this->groupBox17->Text = L"EZViewer";
			// 
			// richTextBox_PacketPosition
			// 
			this->richTextBox_PacketPosition->AutoWordSelection = true;
			this->richTextBox_PacketPosition->Font = (gcnew System::Drawing::Font(L"NSimSun", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->richTextBox_PacketPosition->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->richTextBox_PacketPosition->Location = System::Drawing::Point(6, 19);
			this->richTextBox_PacketPosition->Name = L"richTextBox_PacketPosition";
			this->richTextBox_PacketPosition->ReadOnly = true;
			this->richTextBox_PacketPosition->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
			this->richTextBox_PacketPosition->Size = System::Drawing::Size(66, 302);
			this->richTextBox_PacketPosition->TabIndex = 21;
			this->richTextBox_PacketPosition->Text = resources->GetString(L"richTextBox_PacketPosition.Text");
			this->richTextBox_PacketPosition->WordWrap = false;
			// 
			// groupBox16
			// 
			this->groupBox16->BackColor = System::Drawing::SystemColors::Control;
			this->groupBox16->Controls->Add(this->label21);
			this->groupBox16->Controls->Add(this->label20);
			this->groupBox16->Controls->Add(this->label19);
			this->groupBox16->Controls->Add(this->textBox_ConvStr);
			this->groupBox16->Controls->Add(this->textBox_32Float);
			this->groupBox16->Controls->Add(this->textBox_16Float);
			this->groupBox16->Controls->Add(this->label18);
			this->groupBox16->Controls->Add(this->textBox_8Float);
			this->groupBox16->Controls->Add(this->label16);
			this->groupBox16->Controls->Add(this->label15);
			this->groupBox16->Controls->Add(this->label14);
			this->groupBox16->Controls->Add(this->label13);
			this->groupBox16->Controls->Add(this->textBox_64Int);
			this->groupBox16->Controls->Add(this->textBox_32Int);
			this->groupBox16->Controls->Add(this->textBox_16Int);
			this->groupBox16->Controls->Add(this->textBox_8Int);
			this->groupBox16->Font = (gcnew System::Drawing::Font(L"NSimSun", 7.75F));
			this->groupBox16->Location = System::Drawing::Point(6, 327);
			this->groupBox16->Name = L"groupBox16";
			this->groupBox16->Size = System::Drawing::Size(422, 120);
			this->groupBox16->TabIndex = 28;
			this->groupBox16->TabStop = false;
			this->groupBox16->Text = L"Conversion View";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(154, 77);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(77, 11);
			this->label21->TabIndex = 18;
			this->label21->Text = L"32-Bit Float";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(156, 99);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(41, 11);
			this->label20->TabIndex = 17;
			this->label20->Text = L"String";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(154, 49);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(77, 11);
			this->label19->TabIndex = 16;
			this->label19->Text = L"16-Bit Float";
			// 
			// textBox_ConvStr
			// 
			this->textBox_ConvStr->Location = System::Drawing::Point(236, 96);
			this->textBox_ConvStr->Name = L"textBox_ConvStr";
			this->textBox_ConvStr->Size = System::Drawing::Size(172, 19);
			this->textBox_ConvStr->TabIndex = 14;
			// 
			// textBox_32Float
			// 
			this->textBox_32Float->Location = System::Drawing::Point(236, 72);
			this->textBox_32Float->Name = L"textBox_32Float";
			this->textBox_32Float->Size = System::Drawing::Size(70, 19);
			this->textBox_32Float->TabIndex = 13;
			// 
			// textBox_16Float
			// 
			this->textBox_16Float->Location = System::Drawing::Point(237, 46);
			this->textBox_16Float->Name = L"textBox_16Float";
			this->textBox_16Float->Size = System::Drawing::Size(69, 19);
			this->textBox_16Float->TabIndex = 12;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(156, 20);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(71, 11);
			this->label18->TabIndex = 11;
			this->label18->Text = L"8-Bit Float";
			// 
			// textBox_8Float
			// 
			this->textBox_8Float->Font = (gcnew System::Drawing::Font(L"NSimSun", 7.75F));
			this->textBox_8Float->Location = System::Drawing::Point(237, 17);
			this->textBox_8Float->Name = L"textBox_8Float";
			this->textBox_8Float->Size = System::Drawing::Size(69, 19);
			this->textBox_8Float->TabIndex = 10;
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(9, 97);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(65, 11);
			this->label16->TabIndex = 8;
			this->label16->Text = L"64-Bit Int";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(9, 72);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(65, 11);
			this->label15->TabIndex = 7;
			this->label15->Text = L"32-Bit Int";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(9, 46);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(65, 11);
			this->label14->TabIndex = 6;
			this->label14->Text = L"16-Bit Int";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(9, 20);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(59, 11);
			this->label13->TabIndex = 5;
			this->label13->Text = L"8-Bit Int";
			// 
			// textBox_64Int
			// 
			this->textBox_64Int->Location = System::Drawing::Point(83, 95);
			this->textBox_64Int->Name = L"textBox_64Int";
			this->textBox_64Int->Size = System::Drawing::Size(67, 19);
			this->textBox_64Int->TabIndex = 3;
			// 
			// textBox_32Int
			// 
			this->textBox_32Int->Location = System::Drawing::Point(83, 69);
			this->textBox_32Int->Name = L"textBox_32Int";
			this->textBox_32Int->Size = System::Drawing::Size(67, 19);
			this->textBox_32Int->TabIndex = 2;
			// 
			// textBox_16Int
			// 
			this->textBox_16Int->Location = System::Drawing::Point(83, 43);
			this->textBox_16Int->Name = L"textBox_16Int";
			this->textBox_16Int->Size = System::Drawing::Size(67, 19);
			this->textBox_16Int->TabIndex = 1;
			// 
			// textBox_8Int
			// 
			this->textBox_8Int->Location = System::Drawing::Point(83, 17);
			this->textBox_8Int->Name = L"textBox_8Int";
			this->textBox_8Int->Size = System::Drawing::Size(67, 19);
			this->textBox_8Int->TabIndex = 0;
			// 
			// richTextBox_PacketInspector
			// 
			this->richTextBox_PacketInspector->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox_PacketInspector->Font = (gcnew System::Drawing::Font(L"NSimSun", 9.75F));
			this->richTextBox_PacketInspector->Location = System::Drawing::Point(72, 22);
			this->richTextBox_PacketInspector->Name = L"richTextBox_PacketInspector";
			this->richTextBox_PacketInspector->ReadOnly = true;
			this->richTextBox_PacketInspector->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::ForcedVertical;
			this->richTextBox_PacketInspector->Size = System::Drawing::Size(356, 302);
			this->richTextBox_PacketInspector->TabIndex = 22;
			this->richTextBox_PacketInspector->Text = resources->GetString(L"richTextBox_PacketInspector.Text");
			this->richTextBox_PacketInspector->SelectionChanged += gcnew System::EventHandler(this, &MainForm::richTextBox_PacketInspector_SelectionChanged);
			// 
			// richTextBox_PositionCounter
			// 
			this->richTextBox_PositionCounter->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox_PositionCounter->Font = (gcnew System::Drawing::Font(L"NSimSun", 9.75F));
			this->richTextBox_PositionCounter->ForeColor = System::Drawing::Color::Brown;
			this->richTextBox_PositionCounter->Location = System::Drawing::Point(73, 3);
			this->richTextBox_PositionCounter->Name = L"richTextBox_PositionCounter";
			this->richTextBox_PositionCounter->ReadOnly = true;
			this->richTextBox_PositionCounter->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
			this->richTextBox_PositionCounter->Size = System::Drawing::Size(337, 16);
			this->richTextBox_PositionCounter->TabIndex = 24;
			this->richTextBox_PositionCounter->Text = L"00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n";
			// 
			// checkBox_LogRecv
			// 
			this->checkBox_LogRecv->AutoSize = true;
			this->checkBox_LogRecv->Enabled = false;
			this->checkBox_LogRecv->Location = System::Drawing::Point(5, 467);
			this->checkBox_LogRecv->Name = L"checkBox_LogRecv";
			this->checkBox_LogRecv->Size = System::Drawing::Size(86, 17);
			this->checkBox_LogRecv->TabIndex = 20;
			this->checkBox_LogRecv->Text = L"Log Inbound";
			this->checkBox_LogRecv->UseVisualStyleBackColor = true;
			// 
			// button_SendPacket
			// 
			this->button_SendPacket->Location = System::Drawing::Point(576, 456);
			this->button_SendPacket->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button_SendPacket->Name = L"button_SendPacket";
			this->button_SendPacket->Size = System::Drawing::Size(58, 22);
			this->button_SendPacket->TabIndex = 19;
			this->button_SendPacket->Text = L"Send Outbound";
			this->button_SendPacket->UseVisualStyleBackColor = true;
			this->button_SendPacket->Click += gcnew System::EventHandler(this, &MainForm::button_SendPacket_Click);
			// 
			// textBox_SendPacketInput
			// 
			this->textBox_SendPacketInput->Location = System::Drawing::Point(108, 457);
			this->textBox_SendPacketInput->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->textBox_SendPacketInput->Name = L"textBox_SendPacketInput";
			this->textBox_SendPacketInput->Size = System::Drawing::Size(464, 20);
			this->textBox_SendPacketInput->TabIndex = 18;
			this->textBox_SendPacketInput->Text = L"Packet to Send...";
			// 
			// checkBox_LogSP
			// 
			this->checkBox_LogSP->AutoSize = true;
			this->checkBox_LogSP->Location = System::Drawing::Point(5, 447);
			this->checkBox_LogSP->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox_LogSP->Name = L"checkBox_LogSP";
			this->checkBox_LogSP->Size = System::Drawing::Size(94, 17);
			this->checkBox_LogSP->TabIndex = 2;
			this->checkBox_LogSP->Text = L"Log Outbound";
			this->checkBox_LogSP->UseVisualStyleBackColor = true;
			this->checkBox_LogSP->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_LogSP_CheckedChanged);
			// 
			// listView_Packets
			// 
			this->listView_Packets->AllowColumnReorder = true;
			this->listView_Packets->AutoArrange = false;
			this->listView_Packets->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->listView_Packets->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->columnHeader_SPLength,
					this->columnHeader_SPOpcode, this->columnHeader_SPData
			});
			this->listView_Packets->ContextMenuStrip = this->contextMenuStrip_Packets;
			this->listView_Packets->FullRowSelect = true;
			this->listView_Packets->GridLines = true;
			this->listView_Packets->HideSelection = false;
			this->listView_Packets->Location = System::Drawing::Point(5, 6);
			this->listView_Packets->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->listView_Packets->Name = L"listView_Packets";
			this->listView_Packets->Size = System::Drawing::Size(627, 435);
			this->listView_Packets->TabIndex = 0;
			this->listView_Packets->UseCompatibleStateImageBehavior = false;
			this->listView_Packets->View = System::Windows::Forms::View::Details;
			this->listView_Packets->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::listView_Packets_SelectedIndexChanged);
			// 
			// columnHeader_SPLength
			// 
			this->columnHeader_SPLength->Tag = L"";
			this->columnHeader_SPLength->Text = L"Length";
			this->columnHeader_SPLength->Width = 57;
			// 
			// columnHeader_SPOpcode
			// 
			this->columnHeader_SPOpcode->Text = L"Opcode";
			this->columnHeader_SPOpcode->Width = 59;
			// 
			// columnHeader_SPData
			// 
			this->columnHeader_SPData->Text = L"Data";
			this->columnHeader_SPData->Width = 874;
			// 
			// tabPage_Hacks
			// 
			this->tabPage_Hacks->BackColor = System::Drawing::Color::Transparent;
			this->tabPage_Hacks->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->tabPage_Hacks->Controls->Add(this->groupBox14);
			this->tabPage_Hacks->Controls->Add(this->groupBox10);
			this->tabPage_Hacks->Controls->Add(this->groupBox7);
			this->tabPage_Hacks->Controls->Add(this->groupBox6);
			this->tabPage_Hacks->Controls->Add(this->groupBox_Entities);
			this->tabPage_Hacks->Controls->Add(this->groupBox1);
			this->tabPage_Hacks->Controls->Add(this->groupBox_Utilities);
			this->tabPage_Hacks->Location = System::Drawing::Point(4, 22);
			this->tabPage_Hacks->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->tabPage_Hacks->Name = L"tabPage_Hacks";
			this->tabPage_Hacks->Padding = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->tabPage_Hacks->Size = System::Drawing::Size(642, 486);
			this->tabPage_Hacks->TabIndex = 0;
			this->tabPage_Hacks->Text = L"Mods";
			// 
			// groupBox14
			// 
			this->groupBox14->Controls->Add(this->checkBox_ShowHPBars);
			this->groupBox14->Controls->Add(this->checkBox_Zoom);
			this->groupBox14->Controls->Add(this->checkBox_IncreaseLights);
			this->groupBox14->Controls->Add(this->checkBox_Dynamite);
			this->groupBox14->Controls->Add(this->checkBox_MapHack);
			this->groupBox14->Controls->Add(this->checkBox_CraftExploit);
			this->groupBox14->Location = System::Drawing::Point(6, 160);
			this->groupBox14->Name = L"groupBox14";
			this->groupBox14->Size = System::Drawing::Size(190, 175);
			this->groupBox14->TabIndex = 34;
			this->groupBox14->TabStop = false;
			this->groupBox14->Text = L"Mods";
			// 
			// checkBox_ShowHPBars
			// 
			this->checkBox_ShowHPBars->AutoSize = true;
			this->checkBox_ShowHPBars->Location = System::Drawing::Point(6, 63);
			this->checkBox_ShowHPBars->Name = L"checkBox_ShowHPBars";
			this->checkBox_ShowHPBars->Size = System::Drawing::Size(130, 17);
			this->checkBox_ShowHPBars->TabIndex = 31;
			this->checkBox_ShowHPBars->Text = L"Show Enemy HP Bars";
			this->checkBox_ShowHPBars->UseVisualStyleBackColor = true;
			this->checkBox_ShowHPBars->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_ShowHPBars_CheckedChanged);
			// 
			// checkBox_Zoom
			// 
			this->checkBox_Zoom->AutoSize = true;
			this->checkBox_Zoom->Location = System::Drawing::Point(7, 21);
			this->checkBox_Zoom->Name = L"checkBox_Zoom";
			this->checkBox_Zoom->Size = System::Drawing::Size(99, 17);
			this->checkBox_Zoom->TabIndex = 32;
			this->checkBox_Zoom->Text = L"No Zoom Limits";
			this->checkBox_Zoom->UseVisualStyleBackColor = true;
			this->checkBox_Zoom->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_Zoom_CheckedChanged);
			// 
			// checkBox_IncreaseLights
			// 
			this->checkBox_IncreaseLights->AutoSize = true;
			this->checkBox_IncreaseLights->Location = System::Drawing::Point(6, 41);
			this->checkBox_IncreaseLights->Name = L"checkBox_IncreaseLights";
			this->checkBox_IncreaseLights->Size = System::Drawing::Size(104, 17);
			this->checkBox_IncreaseLights->TabIndex = 8;
			this->checkBox_IncreaseLights->Text = L"Extreme Lighting";
			this->checkBox_IncreaseLights->UseVisualStyleBackColor = true;
			this->checkBox_IncreaseLights->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_IncreaseLights_CheckedChanged);
			// 
			// checkBox_Dynamite
			// 
			this->checkBox_Dynamite->AutoSize = true;
			this->checkBox_Dynamite->Location = System::Drawing::Point(6, 84);
			this->checkBox_Dynamite->Name = L"checkBox_Dynamite";
			this->checkBox_Dynamite->Size = System::Drawing::Size(169, 17);
			this->checkBox_Dynamite->TabIndex = 29;
			this->checkBox_Dynamite->Text = L"Replace Attack with Dynamite";
			this->checkBox_Dynamite->UseVisualStyleBackColor = true;
			this->checkBox_Dynamite->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_Dynamite_CheckedChanged);
			// 
			// checkBox_MapHack
			// 
			this->checkBox_MapHack->AutoSize = true;
			this->checkBox_MapHack->ForeColor = System::Drawing::Color::Black;
			this->checkBox_MapHack->Location = System::Drawing::Point(6, 106);
			this->checkBox_MapHack->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox_MapHack->Name = L"checkBox_MapHack";
			this->checkBox_MapHack->Size = System::Drawing::Size(120, 17);
			this->checkBox_MapHack->TabIndex = 0;
			this->checkBox_MapHack->Text = L"Reveal Map Always";
			this->checkBox_MapHack->UseVisualStyleBackColor = true;
			this->checkBox_MapHack->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_MapHack_CheckedChanged);
			// 
			// checkBox_CraftExploit
			// 
			this->checkBox_CraftExploit->AutoSize = true;
			this->checkBox_CraftExploit->Enabled = false;
			this->checkBox_CraftExploit->Location = System::Drawing::Point(6, 130);
			this->checkBox_CraftExploit->Name = L"checkBox_CraftExploit";
			this->checkBox_CraftExploit->Size = System::Drawing::Size(174, 17);
			this->checkBox_CraftExploit->TabIndex = 24;
			this->checkBox_CraftExploit->Text = L"Unwilting Crops (Sacred Grove)";
			this->checkBox_CraftExploit->UseVisualStyleBackColor = true;
			this->checkBox_CraftExploit->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_CraftExploit_CheckedChanged);
			// 
			// groupBox10
			// 
			this->groupBox10->BackColor = System::Drawing::Color::Transparent;
			this->groupBox10->Controls->Add(this->button1);
			this->groupBox10->Controls->Add(this->checkBox_Hotkeys);
			this->groupBox10->ForeColor = System::Drawing::Color::Black;
			this->groupBox10->Location = System::Drawing::Point(453, 436);
			this->groupBox10->Name = L"groupBox10";
			this->groupBox10->Size = System::Drawing::Size(182, 45);
			this->groupBox10->TabIndex = 9;
			this->groupBox10->TabStop = false;
			this->groupBox10->Text = L"Hotkeys";
			// 
			// button1
			// 
			this->button1->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button1->Location = System::Drawing::Point(75, 15);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(93, 23);
			this->button1->TabIndex = 10;
			this->button1->Text = L"Show Hotkeys";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// checkBox_Hotkeys
			// 
			this->checkBox_Hotkeys->AutoSize = true;
			this->checkBox_Hotkeys->Location = System::Drawing::Point(9, 21);
			this->checkBox_Hotkeys->Name = L"checkBox_Hotkeys";
			this->checkBox_Hotkeys->Size = System::Drawing::Size(59, 17);
			this->checkBox_Hotkeys->TabIndex = 0;
			this->checkBox_Hotkeys->Text = L"Enable";
			this->checkBox_Hotkeys->UseVisualStyleBackColor = true;
			this->checkBox_Hotkeys->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_Hotkeys_CheckedChanged);
			// 
			// groupBox7
			// 
			this->groupBox7->BackColor = System::Drawing::Color::Transparent;
			this->groupBox7->Controls->Add(this->checkBox_LogEntityLabels);
			this->groupBox7->Controls->Add(this->checkBox_MuteConsole);
			this->groupBox7->Controls->Add(this->button_AddIgnoredEntity);
			this->groupBox7->Controls->Add(this->textBox_IgnoreEntity);
			this->groupBox7->Controls->Add(this->checkBox_LogEntity);
			this->groupBox7->ForeColor = System::Drawing::Color::Black;
			this->groupBox7->Location = System::Drawing::Point(208, 119);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(228, 152);
			this->groupBox7->TabIndex = 7;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"Entities and Components";
			// 
			// checkBox_LogEntityLabels
			// 
			this->checkBox_LogEntityLabels->AutoSize = true;
			this->checkBox_LogEntityLabels->Checked = true;
			this->checkBox_LogEntityLabels->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox_LogEntityLabels->Location = System::Drawing::Point(8, 43);
			this->checkBox_LogEntityLabels->Name = L"checkBox_LogEntityLabels";
			this->checkBox_LogEntityLabels->Size = System::Drawing::Size(107, 17);
			this->checkBox_LogEntityLabels->TabIndex = 22;
			this->checkBox_LogEntityLabels->Text = L"Log Entity Labels";
			this->checkBox_LogEntityLabels->UseVisualStyleBackColor = true;
			this->checkBox_LogEntityLabels->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_LogEntityLabels_CheckedChanged);
			// 
			// checkBox_MuteConsole
			// 
			this->checkBox_MuteConsole->AutoSize = true;
			this->checkBox_MuteConsole->Checked = true;
			this->checkBox_MuteConsole->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox_MuteConsole->Location = System::Drawing::Point(8, 77);
			this->checkBox_MuteConsole->Name = L"checkBox_MuteConsole";
			this->checkBox_MuteConsole->Size = System::Drawing::Size(91, 17);
			this->checkBox_MuteConsole->TabIndex = 21;
			this->checkBox_MuteConsole->Text = L"Mute Console";
			this->checkBox_MuteConsole->UseVisualStyleBackColor = true;
			this->checkBox_MuteConsole->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_MuteConsole_CheckedChanged);
			// 
			// button_AddIgnoredEntity
			// 
			this->button_AddIgnoredEntity->ForeColor = System::Drawing::Color::Black;
			this->button_AddIgnoredEntity->Location = System::Drawing::Point(6, 123);
			this->button_AddIgnoredEntity->Name = L"button_AddIgnoredEntity";
			this->button_AddIgnoredEntity->Size = System::Drawing::Size(216, 23);
			this->button_AddIgnoredEntity->TabIndex = 19;
			this->button_AddIgnoredEntity->Text = L"Ignore Entity";
			this->button_AddIgnoredEntity->UseVisualStyleBackColor = true;
			this->button_AddIgnoredEntity->Click += gcnew System::EventHandler(this, &MainForm::button_AddIgnoredEntity_Click);
			// 
			// textBox_IgnoreEntity
			// 
			this->textBox_IgnoreEntity->Location = System::Drawing::Point(6, 100);
			this->textBox_IgnoreEntity->Name = L"textBox_IgnoreEntity";
			this->textBox_IgnoreEntity->Size = System::Drawing::Size(216, 20);
			this->textBox_IgnoreEntity->TabIndex = 18;
			this->textBox_IgnoreEntity->Text = L"Entity File Path...";
			// 
			// checkBox_LogEntity
			// 
			this->checkBox_LogEntity->AutoSize = true;
			this->checkBox_LogEntity->Checked = true;
			this->checkBox_LogEntity->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox_LogEntity->ForeColor = System::Drawing::Color::Black;
			this->checkBox_LogEntity->Location = System::Drawing::Point(8, 21);
			this->checkBox_LogEntity->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox_LogEntity->Name = L"checkBox_LogEntity";
			this->checkBox_LogEntity->Size = System::Drawing::Size(201, 17);
			this->checkBox_LogEntity->TabIndex = 1;
			this->checkBox_LogEntity->Text = L"Log Entity Data (Required for botting)";
			this->checkBox_LogEntity->UseVisualStyleBackColor = true;
			this->checkBox_LogEntity->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_LogEntity_CheckedChanged);
			// 
			// groupBox6
			// 
			this->groupBox6->BackColor = System::Drawing::Color::Transparent;
			this->groupBox6->Controls->Add(this->comboBox_FollowMovementSkill);
			this->groupBox6->Controls->Add(this->checkBox_Follow);
			this->groupBox6->Controls->Add(this->textBox_FollowCharName);
			this->groupBox6->ForeColor = System::Drawing::Color::Black;
			this->groupBox6->Location = System::Drawing::Point(6, 342);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(196, 132);
			this->groupBox6->TabIndex = 4;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Auto-Follow Player";
			// 
			// comboBox_FollowMovementSkill
			// 
			this->comboBox_FollowMovementSkill->FormattingEnabled = true;
			this->comboBox_FollowMovementSkill->Items->AddRange(gcnew cli::array< System::Object^  >(25) {
				L"Run", L"Helmet 1", L"Helmet 2",
					L"Helmet 3", L"Helmet 4", L"Body 1", L"Body 2", L"Body 3", L"Body 4", L"Body 5", L"Body 6", L"Gloves 1", L"Gloves 2", L"Gloves 3",
					L"Gloves 4", L"Boots 1", L"Boots 2", L"Boots 3", L"Boots 4", L"LeftHand 1", L"LeftHand 2", L"LeftHand 3", L"RightHand 1", L"RightHand 2",
					L"RightHand 3"
			});
			this->comboBox_FollowMovementSkill->Location = System::Drawing::Point(6, 51);
			this->comboBox_FollowMovementSkill->Name = L"comboBox_FollowMovementSkill";
			this->comboBox_FollowMovementSkill->Size = System::Drawing::Size(180, 21);
			this->comboBox_FollowMovementSkill->TabIndex = 23;
			this->comboBox_FollowMovementSkill->Text = L"Run";
			// 
			// checkBox_Follow
			// 
			this->checkBox_Follow->AutoSize = true;
			this->checkBox_Follow->ForeColor = System::Drawing::Color::Black;
			this->checkBox_Follow->Location = System::Drawing::Point(6, 78);
			this->checkBox_Follow->Name = L"checkBox_Follow";
			this->checkBox_Follow->Size = System::Drawing::Size(124, 17);
			this->checkBox_Follow->TabIndex = 12;
			this->checkBox_Follow->Text = L"Enable Follow Player";
			this->checkBox_Follow->UseVisualStyleBackColor = true;
			this->checkBox_Follow->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_Follow_CheckedChanged);
			// 
			// textBox_FollowCharName
			// 
			this->textBox_FollowCharName->Location = System::Drawing::Point(6, 22);
			this->textBox_FollowCharName->Name = L"textBox_FollowCharName";
			this->textBox_FollowCharName->Size = System::Drawing::Size(180, 20);
			this->textBox_FollowCharName->TabIndex = 11;
			this->textBox_FollowCharName->Text = L"Name...";
			// 
			// groupBox_Entities
			// 
			this->groupBox_Entities->BackColor = System::Drawing::Color::Transparent;
			this->groupBox_Entities->Controls->Add(this->label_PlayerClass);
			this->groupBox_Entities->Controls->Add(this->label_Exp);
			this->groupBox_Entities->Controls->Add(this->label_Level);
			this->groupBox_Entities->Controls->Add(this->label_Status);
			this->groupBox_Entities->Controls->Add(this->label_GridY);
			this->groupBox_Entities->Controls->Add(this->checkBox_DisplayPlayerData);
			this->groupBox_Entities->Controls->Add(this->label_GridX);
			this->groupBox_Entities->Controls->Add(this->label5);
			this->groupBox_Entities->Controls->Add(this->label_PlayerES);
			this->groupBox_Entities->Controls->Add(this->label_MP);
			this->groupBox_Entities->Controls->Add(this->label_HP);
			this->groupBox_Entities->ForeColor = System::Drawing::Color::Black;
			this->groupBox_Entities->Location = System::Drawing::Point(450, 9);
			this->groupBox_Entities->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->groupBox_Entities->Name = L"groupBox_Entities";
			this->groupBox_Entities->Padding = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->groupBox_Entities->Size = System::Drawing::Size(182, 270);
			this->groupBox_Entities->TabIndex = 3;
			this->groupBox_Entities->TabStop = false;
			this->groupBox_Entities->Text = L"LocalPlayer";
			// 
			// label_PlayerClass
			// 
			this->label_PlayerClass->AutoSize = true;
			this->label_PlayerClass->Location = System::Drawing::Point(4, 123);
			this->label_PlayerClass->Name = L"label_PlayerClass";
			this->label_PlayerClass->Size = System::Drawing::Size(38, 13);
			this->label_PlayerClass->TabIndex = 20;
			this->label_PlayerClass->Text = L"Class: ";
			// 
			// label_Exp
			// 
			this->label_Exp->AutoSize = true;
			this->label_Exp->Location = System::Drawing::Point(4, 166);
			this->label_Exp->Name = L"label_Exp";
			this->label_Exp->Size = System::Drawing::Size(66, 13);
			this->label_Exp->TabIndex = 19;
			this->label_Exp->Text = L"Experience: ";
			// 
			// label_Level
			// 
			this->label_Level->AutoSize = true;
			this->label_Level->Location = System::Drawing::Point(4, 144);
			this->label_Level->Name = L"label_Level";
			this->label_Level->Size = System::Drawing::Size(39, 13);
			this->label_Level->TabIndex = 18;
			this->label_Level->Text = L"Level: ";
			// 
			// label_Status
			// 
			this->label_Status->AutoSize = true;
			this->label_Status->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_Status->ForeColor = System::Drawing::Color::Maroon;
			this->label_Status->Location = System::Drawing::Point(3, 22);
			this->label_Status->Name = L"label_Status";
			this->label_Status->Size = System::Drawing::Size(79, 13);
			this->label_Status->TabIndex = 18;
			this->label_Status->Text = L"Status: IDLE";
			// 
			// label_GridY
			// 
			this->label_GridY->AutoSize = true;
			this->label_GridY->Location = System::Drawing::Point(83, 213);
			this->label_GridY->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label_GridY->Name = L"label_GridY";
			this->label_GridY->Size = System::Drawing::Size(17, 13);
			this->label_GridY->TabIndex = 13;
			this->label_GridY->Text = L"Y:";
			// 
			// checkBox_DisplayPlayerData
			// 
			this->checkBox_DisplayPlayerData->AutoSize = true;
			this->checkBox_DisplayPlayerData->Location = System::Drawing::Point(8, 245);
			this->checkBox_DisplayPlayerData->Margin = System::Windows::Forms::Padding(1, 4, 1, 4);
			this->checkBox_DisplayPlayerData->Name = L"checkBox_DisplayPlayerData";
			this->checkBox_DisplayPlayerData->Size = System::Drawing::Size(147, 17);
			this->checkBox_DisplayPlayerData->TabIndex = 3;
			this->checkBox_DisplayPlayerData->Text = L"Display Local Player Data";
			this->checkBox_DisplayPlayerData->UseVisualStyleBackColor = true;
			this->checkBox_DisplayPlayerData->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_DisplayPlayerData_CheckedChanged);
			// 
			// label_GridX
			// 
			this->label_GridX->AutoSize = true;
			this->label_GridX->Location = System::Drawing::Point(8, 213);
			this->label_GridX->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label_GridX->Name = L"label_GridX";
			this->label_GridX->Size = System::Drawing::Size(20, 13);
			this->label_GridX->TabIndex = 12;
			this->label_GridX->Text = L"X: ";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->ForeColor = System::Drawing::Color::Black;
			this->label5->Location = System::Drawing::Point(4, 191);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(138, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Network Grid Position (2D): ";
			// 
			// label_PlayerES
			// 
			this->label_PlayerES->AutoSize = true;
			this->label_PlayerES->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label_PlayerES->Location = System::Drawing::Point(3, 98);
			this->label_PlayerES->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label_PlayerES->Name = L"label_PlayerES";
			this->label_PlayerES->Size = System::Drawing::Size(78, 13);
			this->label_PlayerES->TabIndex = 9;
			this->label_PlayerES->Text = L"Energy Shield: ";
			// 
			// label_MP
			// 
			this->label_MP->AutoSize = true;
			this->label_MP->ForeColor = System::Drawing::Color::Blue;
			this->label_MP->Location = System::Drawing::Point(3, 72);
			this->label_MP->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label_MP->Name = L"label_MP";
			this->label_MP->Size = System::Drawing::Size(40, 13);
			this->label_MP->TabIndex = 5;
			this->label_MP->Text = L"Mana: ";
			// 
			// label_HP
			// 
			this->label_HP->AutoSize = true;
			this->label_HP->ForeColor = System::Drawing::Color::DarkRed;
			this->label_HP->Location = System::Drawing::Point(3, 47);
			this->label_HP->Margin = System::Windows::Forms::Padding(1, 0, 1, 0);
			this->label_HP->Name = L"label_HP";
			this->label_HP->Size = System::Drawing::Size(44, 13);
			this->label_HP->TabIndex = 4;
			this->label_HP->Text = L"Health: ";
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::Color::Transparent;
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->numericUpDown_CPUReducerTime);
			this->groupBox1->Controls->Add(this->checkBox_StopRender);
			this->groupBox1->Controls->Add(this->checkBox_ReduceCPU);
			this->groupBox1->Controls->Add(this->checkBox_RAMReduce);
			this->groupBox1->ForeColor = System::Drawing::Color::Black;
			this->groupBox1->Location = System::Drawing::Point(174, 9);
			this->groupBox1->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->groupBox1->Size = System::Drawing::Size(265, 99);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Resources";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(130, 44);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(73, 13);
			this->label4->TabIndex = 4;
			this->label4->Text = L"Reducer (ms):";
			// 
			// numericUpDown_CPUReducerTime
			// 
			this->numericUpDown_CPUReducerTime->Location = System::Drawing::Point(207, 41);
			this->numericUpDown_CPUReducerTime->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->numericUpDown_CPUReducerTime->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown_CPUReducerTime->Name = L"numericUpDown_CPUReducerTime";
			this->numericUpDown_CPUReducerTime->Size = System::Drawing::Size(50, 20);
			this->numericUpDown_CPUReducerTime->TabIndex = 3;
			this->numericUpDown_CPUReducerTime->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, 0 });
			// 
			// checkBox_StopRender
			// 
			this->checkBox_StopRender->AutoSize = true;
			this->checkBox_StopRender->Enabled = false;
			this->checkBox_StopRender->Location = System::Drawing::Point(6, 67);
			this->checkBox_StopRender->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox_StopRender->Name = L"checkBox_StopRender";
			this->checkBox_StopRender->Size = System::Drawing::Size(100, 17);
			this->checkBox_StopRender->TabIndex = 2;
			this->checkBox_StopRender->Text = L"Stop Rendering";
			this->checkBox_StopRender->UseVisualStyleBackColor = true;
			// 
			// checkBox_ReduceCPU
			// 
			this->checkBox_ReduceCPU->AutoSize = true;
			this->checkBox_ReduceCPU->Location = System::Drawing::Point(6, 43);
			this->checkBox_ReduceCPU->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox_ReduceCPU->Name = L"checkBox_ReduceCPU";
			this->checkBox_ReduceCPU->Size = System::Drawing::Size(123, 17);
			this->checkBox_ReduceCPU->TabIndex = 1;
			this->checkBox_ReduceCPU->Text = L"Reduce CPU Usage";
			this->checkBox_ReduceCPU->UseVisualStyleBackColor = true;
			this->checkBox_ReduceCPU->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_ReduceCPU_CheckedChanged);
			// 
			// checkBox_RAMReduce
			// 
			this->checkBox_RAMReduce->AutoSize = true;
			this->checkBox_RAMReduce->Location = System::Drawing::Point(6, 19);
			this->checkBox_RAMReduce->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->checkBox_RAMReduce->Name = L"checkBox_RAMReduce";
			this->checkBox_RAMReduce->Size = System::Drawing::Size(94, 17);
			this->checkBox_RAMReduce->TabIndex = 0;
			this->checkBox_RAMReduce->Text = L"Reduce RAM ";
			this->checkBox_RAMReduce->UseVisualStyleBackColor = true;
			this->checkBox_RAMReduce->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_RAMReduce_CheckedChanged);
			// 
			// groupBox_Utilities
			// 
			this->groupBox_Utilities->BackColor = System::Drawing::Color::Transparent;
			this->groupBox_Utilities->Controls->Add(this->checkBox_LogHoveredElements);
			this->groupBox_Utilities->Controls->Add(this->checkBox_NullTerrain);
			this->groupBox_Utilities->Controls->Add(this->checkBox_HookClientMsg);
			this->groupBox_Utilities->Controls->Add(this->button_RevealMap);
			this->groupBox_Utilities->ForeColor = System::Drawing::Color::Black;
			this->groupBox_Utilities->Location = System::Drawing::Point(6, 4);
			this->groupBox_Utilities->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->groupBox_Utilities->Name = L"groupBox_Utilities";
			this->groupBox_Utilities->Padding = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->groupBox_Utilities->Size = System::Drawing::Size(155, 127);
			this->groupBox_Utilities->TabIndex = 1;
			this->groupBox_Utilities->TabStop = false;
			this->groupBox_Utilities->Text = L"Utility";
			// 
			// checkBox_LogHoveredElements
			// 
			this->checkBox_LogHoveredElements->AutoSize = true;
			this->checkBox_LogHoveredElements->Location = System::Drawing::Point(9, 95);
			this->checkBox_LogHoveredElements->Name = L"checkBox_LogHoveredElements";
			this->checkBox_LogHoveredElements->Size = System::Drawing::Size(134, 17);
			this->checkBox_LogHoveredElements->TabIndex = 27;
			this->checkBox_LogHoveredElements->Text = L"Log Hovered Elements";
			this->checkBox_LogHoveredElements->UseVisualStyleBackColor = true;
			this->checkBox_LogHoveredElements->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_LogHoveredElements_CheckedChanged);
			// 
			// checkBox_NullTerrain
			// 
			this->checkBox_NullTerrain->AutoSize = true;
			this->checkBox_NullTerrain->Location = System::Drawing::Point(9, 45);
			this->checkBox_NullTerrain->Name = L"checkBox_NullTerrain";
			this->checkBox_NullTerrain->Size = System::Drawing::Size(90, 17);
			this->checkBox_NullTerrain->TabIndex = 33;
			this->checkBox_NullTerrain->Text = L"NULL Terrain";
			this->checkBox_NullTerrain->UseVisualStyleBackColor = true;
			this->checkBox_NullTerrain->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_NullTerrain_CheckedChanged);
			// 
			// checkBox_HookClientMsg
			// 
			this->checkBox_HookClientMsg->AutoSize = true;
			this->checkBox_HookClientMsg->Checked = true;
			this->checkBox_HookClientMsg->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox_HookClientMsg->Location = System::Drawing::Point(9, 70);
			this->checkBox_HookClientMsg->Name = L"checkBox_HookClientMsg";
			this->checkBox_HookClientMsg->Size = System::Drawing::Size(132, 17);
			this->checkBox_HookClientMsg->TabIndex = 23;
			this->checkBox_HookClientMsg->Text = L"Hook Client Messages";
			this->checkBox_HookClientMsg->UseVisualStyleBackColor = true;
			this->checkBox_HookClientMsg->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_HookClientMsg_CheckedChanged);
			// 
			// button_RevealMap
			// 
			this->button_RevealMap->ForeColor = System::Drawing::Color::Black;
			this->button_RevealMap->Location = System::Drawing::Point(7, 17);
			this->button_RevealMap->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->button_RevealMap->Name = L"button_RevealMap";
			this->button_RevealMap->Size = System::Drawing::Size(129, 22);
			this->button_RevealMap->TabIndex = 2;
			this->button_RevealMap->Text = L"Reveal Map Once (F3)";
			this->button_RevealMap->UseVisualStyleBackColor = true;
			this->button_RevealMap->Click += gcnew System::EventHandler(this, &MainForm::button_RevealMap_Click);
			// 
			// tabPage_LUA
			// 
			this->tabPage_LUA->BackColor = System::Drawing::Color::Transparent;
			this->tabPage_LUA->Controls->Add(this->groupBox3);
			this->tabPage_LUA->Controls->Add(this->textBox_ScriptText);
			this->tabPage_LUA->Location = System::Drawing::Point(4, 22);
			this->tabPage_LUA->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->tabPage_LUA->Name = L"tabPage_LUA";
			this->tabPage_LUA->Size = System::Drawing::Size(642, 486);
			this->tabPage_LUA->TabIndex = 3;
			this->tabPage_LUA->Text = L"Scripting";
			// 
			// groupBox3
			// 
			this->groupBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->groupBox3->BackColor = System::Drawing::Color::Transparent;
			this->groupBox3->Controls->Add(this->checkBox_RepeatScript);
			this->groupBox3->Controls->Add(this->checkBox_RandomizingLUAName);
			this->groupBox3->Controls->Add(this->button_DownloadLUA);
			this->groupBox3->Controls->Add(this->button_LoadLUA);
			this->groupBox3->Controls->Add(this->button_SaveLUA);
			this->groupBox3->Controls->Add(this->button_RunLUA);
			this->groupBox3->Controls->Add(this->button_StopLUA);
			this->groupBox3->Location = System::Drawing::Point(13, 407);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(615, 72);
			this->groupBox3->TabIndex = 16;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Scripting Menu";
			// 
			// checkBox_RepeatScript
			// 
			this->checkBox_RepeatScript->AutoSize = true;
			this->checkBox_RepeatScript->Location = System::Drawing::Point(525, 19);
			this->checkBox_RepeatScript->Name = L"checkBox_RepeatScript";
			this->checkBox_RepeatScript->Size = System::Drawing::Size(80, 17);
			this->checkBox_RepeatScript->TabIndex = 20;
			this->checkBox_RepeatScript->Text = L"Loop Script";
			this->checkBox_RepeatScript->UseVisualStyleBackColor = true;
			this->checkBox_RepeatScript->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_RepeatScript_CheckedChanged);
			// 
			// checkBox_RandomizingLUAName
			// 
			this->checkBox_RandomizingLUAName->AutoSize = true;
			this->checkBox_RandomizingLUAName->Location = System::Drawing::Point(461, 47);
			this->checkBox_RandomizingLUAName->Name = L"checkBox_RandomizingLUAName";
			this->checkBox_RandomizingLUAName->Size = System::Drawing::Size(140, 17);
			this->checkBox_RandomizingLUAName->TabIndex = 19;
			this->checkBox_RandomizingLUAName->Text = L"Randomize Script Name";
			this->checkBox_RandomizingLUAName->UseVisualStyleBackColor = true;
			this->checkBox_RandomizingLUAName->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox1_CheckedChanged);
			// 
			// textBox_ScriptText
			// 
			this->textBox_ScriptText->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_ScriptText->BackColor = System::Drawing::Color::White;
			this->textBox_ScriptText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox_ScriptText->Location = System::Drawing::Point(12, 2);
			this->textBox_ScriptText->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->textBox_ScriptText->Multiline = true;
			this->textBox_ScriptText->Name = L"textBox_ScriptText";
			this->textBox_ScriptText->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->textBox_ScriptText->Size = System::Drawing::Size(618, 400);
			this->textBox_ScriptText->TabIndex = 4;
			this->textBox_ScriptText->Text = resources->GetString(L"textBox_ScriptText.Text");
			// 
			// tabControl1
			// 
			this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl1->Controls->Add(this->tabPage_LUA);
			this->tabControl1->Controls->Add(this->tabPage_Hacks);
			this->tabControl1->Controls->Add(this->tabPage_Bot);
			this->tabControl1->Controls->Add(this->tabPage_Packets);
			this->tabControl1->Controls->Add(this->tabPage_TradeBot);
			this->tabControl1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tabControl1->Location = System::Drawing::Point(7, 26);
			this->tabControl1->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(650, 512);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPage_TradeBot
			// 
			this->tabPage_TradeBot->BackColor = System::Drawing::SystemColors::Control;
			this->tabPage_TradeBot->Controls->Add(this->groupBox13);
			this->tabPage_TradeBot->Controls->Add(this->groupBox12);
			this->tabPage_TradeBot->Location = System::Drawing::Point(4, 22);
			this->tabPage_TradeBot->Name = L"tabPage_TradeBot";
			this->tabPage_TradeBot->Size = System::Drawing::Size(642, 486);
			this->tabPage_TradeBot->TabIndex = 5;
			this->tabPage_TradeBot->Text = L"Trade Bot";
			// 
			// groupBox13
			// 
			this->groupBox13->Controls->Add(this->listView1);
			this->groupBox13->Location = System::Drawing::Point(276, 9);
			this->groupBox13->Name = L"groupBox13";
			this->groupBox13->Size = System::Drawing::Size(360, 456);
			this->groupBox13->TabIndex = 2;
			this->groupBox13->TabStop = false;
			this->groupBox13->Text = L"History";
			// 
			// listView1
			// 
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {
				this->columnHeader1, this->columnHeader2,
					this->columnHeader3, this->columnHeader4
			});
			this->listView1->FullRowSelect = true;
			this->listView1->GridLines = true;
			this->listView1->HideSelection = false;
			this->listView1->Location = System::Drawing::Point(9, 21);
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(345, 429);
			this->listView1->TabIndex = 3;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"Date";
			this->columnHeader1->Width = 50;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"Player";
			this->columnHeader2->Width = 51;
			// 
			// columnHeader3
			// 
			this->columnHeader3->Text = L"Exchanged From";
			this->columnHeader3->Width = 102;
			// 
			// columnHeader4
			// 
			this->columnHeader4->Text = L"Exchanged To";
			this->columnHeader4->Width = 175;
			// 
			// groupBox12
			// 
			this->groupBox12->Controls->Add(this->checkBox_AutoSellEverything);
			this->groupBox12->Controls->Add(this->checkBox_LogAutoTradeData);
			this->groupBox12->Controls->Add(this->comboBox_AutoTradeServer);
			this->groupBox12->Controls->Add(this->textBox_AutoBuyItemName);
			this->groupBox12->Controls->Add(this->label11);
			this->groupBox12->Controls->Add(this->comboBox_WTBExchangeItem);
			this->groupBox12->Controls->Add(this->numericUpDown_AutoBuyExchangeQuantity);
			this->groupBox12->Controls->Add(this->label8);
			this->groupBox12->Controls->Add(this->numericUpDown_WTBQuantity);
			this->groupBox12->Controls->Add(this->radioButton_AutoSell);
			this->groupBox12->Controls->Add(this->radioButton_AutoBuy);
			this->groupBox12->Controls->Add(this->checkBox_TradeBot);
			this->groupBox12->Location = System::Drawing::Point(10, 9);
			this->groupBox12->Name = L"groupBox12";
			this->groupBox12->Size = System::Drawing::Size(260, 456);
			this->groupBox12->TabIndex = 1;
			this->groupBox12->TabStop = false;
			this->groupBox12->Text = L"Parameters";
			// 
			// checkBox_AutoSellEverything
			// 
			this->checkBox_AutoSellEverything->AutoSize = true;
			this->checkBox_AutoSellEverything->Checked = true;
			this->checkBox_AutoSellEverything->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox_AutoSellEverything->Location = System::Drawing::Point(12, 177);
			this->checkBox_AutoSellEverything->Name = L"checkBox_AutoSellEverything";
			this->checkBox_AutoSellEverything->Size = System::Drawing::Size(169, 17);
			this->checkBox_AutoSellEverything->TabIndex = 23;
			this->checkBox_AutoSellEverything->Text = L"Respond to all player whispers";
			this->checkBox_AutoSellEverything->UseVisualStyleBackColor = true;
			// 
			// checkBox_LogAutoTradeData
			// 
			this->checkBox_LogAutoTradeData->AutoSize = true;
			this->checkBox_LogAutoTradeData->Location = System::Drawing::Point(136, 431);
			this->checkBox_LogAutoTradeData->Name = L"checkBox_LogAutoTradeData";
			this->checkBox_LogAutoTradeData->Size = System::Drawing::Size(105, 17);
			this->checkBox_LogAutoTradeData->TabIndex = 7;
			this->checkBox_LogAutoTradeData->Text = L"Log Data To File";
			this->checkBox_LogAutoTradeData->UseVisualStyleBackColor = true;
			// 
			// comboBox_AutoTradeServer
			// 
			this->comboBox_AutoTradeServer->FormattingEnabled = true;
			this->comboBox_AutoTradeServer->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Standard", L"Scourge", L"Hardcore",
					L"Scourge Hardcore"
			});
			this->comboBox_AutoTradeServer->Location = System::Drawing::Point(13, 25);
			this->comboBox_AutoTradeServer->Name = L"comboBox_AutoTradeServer";
			this->comboBox_AutoTradeServer->Size = System::Drawing::Size(101, 21);
			this->comboBox_AutoTradeServer->TabIndex = 22;
			this->comboBox_AutoTradeServer->Text = L"Scourge";
			// 
			// textBox_AutoBuyItemName
			// 
			this->textBox_AutoBuyItemName->Location = System::Drawing::Point(86, 80);
			this->textBox_AutoBuyItemName->Name = L"textBox_AutoBuyItemName";
			this->textBox_AutoBuyItemName->Size = System::Drawing::Size(140, 20);
			this->textBox_AutoBuyItemName->TabIndex = 20;
			this->textBox_AutoBuyItemName->Text = L"Item Name...";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(7, 112);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(97, 13);
			this->label11->TabIndex = 18;
			this->label11->Text = L"For maximum price:";
			// 
			// comboBox_WTBExchangeItem
			// 
			this->comboBox_WTBExchangeItem->FormattingEnabled = true;
			this->comboBox_WTBExchangeItem->Items->AddRange(gcnew cli::array< System::Object^  >(35) {
				L"Orb of Alteration", L"Orb of Alchemy",
					L"Orb of Fusing", L"Vaal Orb", L"Gemcutter\'s Prism", L"Chaos Orb", L"Exalted Orb", L"Jeweller\'s Orb", L"Divine Orb", L"Chromatic Orb",
					L"Orb of Chance", L"Cartographer\'s Chisel", L"Orb of Scouring", L"Blessed Orb", L"Orb of Regret", L"Regal Orb", L"Orb of Transmutatiom",
					L"Orb of Augmentation", L"Glassblower\'s Bauble", L"Mirror of Kalandra", L"Eternal Orb", L"Silver Coin", L"Simple Sextant", L"Prime Sextant",
					L"Awakened Sextant", L"Elavated Sextant", L"Orb of Annulment", L"Orb of Binding", L"Orb of Horizons", L"Harbinger\'s Orb", L"Ancient Orb",
					L"Mirror Shard", L"Exalted Shard", L"Annulment Shard", L"Beastiary Orb"
			});
			this->comboBox_WTBExchangeItem->Location = System::Drawing::Point(86, 137);
			this->comboBox_WTBExchangeItem->Name = L"comboBox_WTBExchangeItem";
			this->comboBox_WTBExchangeItem->Size = System::Drawing::Size(140, 21);
			this->comboBox_WTBExchangeItem->TabIndex = 17;
			this->comboBox_WTBExchangeItem->Text = L"Orb of Alchemy";
			// 
			// numericUpDown_AutoBuyExchangeQuantity
			// 
			this->numericUpDown_AutoBuyExchangeQuantity->Location = System::Drawing::Point(11, 137);
			this->numericUpDown_AutoBuyExchangeQuantity->Name = L"numericUpDown_AutoBuyExchangeQuantity";
			this->numericUpDown_AutoBuyExchangeQuantity->Size = System::Drawing::Size(58, 20);
			this->numericUpDown_AutoBuyExchangeQuantity->TabIndex = 16;
			this->numericUpDown_AutoBuyExchangeQuantity->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 8, 0, 0, 0 });
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->ForeColor = System::Drawing::Color::Maroon;
			this->label8->Location = System::Drawing::Point(10, 55);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(74, 13);
			this->label8->TabIndex = 10;
			this->label8->Text = L"Want to buy...";
			// 
			// numericUpDown_WTBQuantity
			// 
			this->numericUpDown_WTBQuantity->Location = System::Drawing::Point(13, 80);
			this->numericUpDown_WTBQuantity->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->numericUpDown_WTBQuantity->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown_WTBQuantity->Name = L"numericUpDown_WTBQuantity";
			this->numericUpDown_WTBQuantity->Size = System::Drawing::Size(58, 20);
			this->numericUpDown_WTBQuantity->TabIndex = 9;
			this->numericUpDown_WTBQuantity->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// radioButton_AutoSell
			// 
			this->radioButton_AutoSell->AutoSize = true;
			this->radioButton_AutoSell->Checked = true;
			this->radioButton_AutoSell->Location = System::Drawing::Point(24, 221);
			this->radioButton_AutoSell->Name = L"radioButton_AutoSell";
			this->radioButton_AutoSell->Size = System::Drawing::Size(66, 17);
			this->radioButton_AutoSell->TabIndex = 5;
			this->radioButton_AutoSell->TabStop = true;
			this->radioButton_AutoSell->Text = L"Sell Only";
			this->radioButton_AutoSell->UseVisualStyleBackColor = true;
			// 
			// radioButton_AutoBuy
			// 
			this->radioButton_AutoBuy->AutoSize = true;
			this->radioButton_AutoBuy->Enabled = false;
			this->radioButton_AutoBuy->Location = System::Drawing::Point(104, 222);
			this->radioButton_AutoBuy->Name = L"radioButton_AutoBuy";
			this->radioButton_AutoBuy->Size = System::Drawing::Size(67, 17);
			this->radioButton_AutoBuy->TabIndex = 4;
			this->radioButton_AutoBuy->Text = L"Buy Only";
			this->radioButton_AutoBuy->UseVisualStyleBackColor = true;
			// 
			// checkBox_TradeBot
			// 
			this->checkBox_TradeBot->AutoSize = true;
			this->checkBox_TradeBot->Location = System::Drawing::Point(12, 199);
			this->checkBox_TradeBot->Name = L"checkBox_TradeBot";
			this->checkBox_TradeBot->Size = System::Drawing::Size(67, 17);
			this->checkBox_TradeBot->TabIndex = 0;
			this->checkBox_TradeBot->Text = L"Start Bot";
			this->checkBox_TradeBot->UseVisualStyleBackColor = true;
			this->checkBox_TradeBot->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox_TradeBot_CheckedChanged);
			// 
			// MainForm
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::ForestGreen;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(669, 550);
			this->ControlBox = false;
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->menuStrip_MainMenu);
			this->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->HelpButton = true;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip_MainMenu;
			this->Margin = System::Windows::Forms::Padding(1, 2, 1, 2);
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->Text = L"Go PoE (3.22) by AlSch092 (Github)";
			this->TransparencyKey = System::Drawing::Color::DimGray;
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->Click += gcnew System::EventHandler(this, &MainForm::MainForm_Click);
			this->contextMenuStrip_Packets->ResumeLayout(false);
			this->menuStrip_MainMenu->ResumeLayout(false);
			this->menuStrip_MainMenu->PerformLayout();
			this->tabPage_Bot->ResumeLayout(false);
			this->tabPage_Bot->PerformLayout();
			this->groupBox15->ResumeLayout(false);
			this->groupBox15->PerformLayout();
			this->groupBox9->ResumeLayout(false);
			this->groupBox9->PerformLayout();
			this->groupBox11->ResumeLayout(false);
			this->groupBox11->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			this->groupBox8->ResumeLayout(false);
			this->groupBox8->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_FlaskES))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_FlaskMP))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_FlaskHP))->EndInit();
			this->tabPage_Packets->ResumeLayout(false);
			this->tabPage_Packets->PerformLayout();
			this->groupBox17->ResumeLayout(false);
			this->groupBox16->ResumeLayout(false);
			this->groupBox16->PerformLayout();
			this->tabPage_Hacks->ResumeLayout(false);
			this->groupBox14->ResumeLayout(false);
			this->groupBox14->PerformLayout();
			this->groupBox10->ResumeLayout(false);
			this->groupBox10->PerformLayout();
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->groupBox_Entities->ResumeLayout(false);
			this->groupBox_Entities->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_CPUReducerTime))->EndInit();
			this->groupBox_Utilities->ResumeLayout(false);
			this->groupBox_Utilities->PerformLayout();
			this->tabPage_LUA->ResumeLayout(false);
			this->tabPage_LUA->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->tabControl1->ResumeLayout(false);
			this->tabPage_TradeBot->ResumeLayout(false);
			this->groupBox13->ResumeLayout(false);
			this->groupBox12->ResumeLayout(false);
			this->groupBox12->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_AutoBuyExchangeQuantity))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_WTBQuantity))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void ProcessSendQueue() {

	if (SendPacketQueue.size() > 0)
	{
		for (int i = 0; i < SendPacketQueue.size(); i++)
		{
			SendPacketQueue.pop();

		}
	}

	while (g_Robot->isLoggingOutbound)
	{
		if (SendPacketQueue.size() > 0)
		{
			PacketWriter* sendPacket = SendPacketQueue.front();

			wchar_t *pwDataText;
			wchar_t pwLengthText[5];

			std::string packetString = PacketHelper::ToString((unsigned char*)sendPacket->GetBuffer(), sendPacket->GetSize());
				
			DWORD dwNum = MultiByteToWideChar(CP_UTF8, 0, packetString.c_str(), -1, NULL, 0);
			_itow_s(sendPacket->GetSize(), pwLengthText, 10);

			pwDataText = new wchar_t[dwNum];
			MultiByteToWideChar(CP_UTF8, 0, packetString.c_str(), -1, pwDataText, dwNum);

			//0x0126
			wchar_t pwOpcodeText[10];
			pwOpcodeText[0] = pwDataText[0];
			pwOpcodeText[1] = pwDataText[1];
			pwOpcodeText[2] = pwDataText[2];
			pwOpcodeText[3] = pwDataText[3];
			pwOpcodeText[4] = pwDataText[4];
			pwOpcodeText[5] = pwDataText[5];
			pwOpcodeText[6] = 0x0000;

			String ^dataString = gcnew String(pwDataText);
			String ^lengthString = gcnew String(pwLengthText);
			String ^OpcodeString = gcnew String(pwOpcodeText);

			cli::array<String^>^ subItems = gcnew cli::array<String^>(3);
			subItems[0] = gcnew String(lengthString);
			subItems[1] = gcnew String(OpcodeString);
			subItems[2] = gcnew String(dataString);

			ListViewItem^ itm = gcnew ListViewItem(subItems);
			this->listView_Packets->Items->Add(itm);

			SendPacketQueue.pop();
		
			delete sendPacket;
			delete[] pwDataText;
		
		}
		else
			Thread::Sleep(300);
	}
}

private: System::Void Intro()
{
	//Thread::Sleep(3000);
	//this->label_IntroMessage->Text = "Client is up to date. Enjoy!";
	//Thread::Sleep(3000);
	//this->pictureBox_Intro->Visible = false;
	//this->label_IntroMessage->Visible = false;
	//this->label_IntroGreeting->Visible = false;
}

private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {

	if (gClientBase == 0)
	{
		gClientBase = (UINT64)GetModuleHandleW(L"PathOfExile.exe");

		UINT64 Version = gClientBase + g_ProtectionServer->Offsets[12];//Offsets::Pointers::ClientVersion;
		printf("Client Version: %s\n", (char*)Version);

		if (strcmp((const char*)Version, "3.23.0") != 0)
		{
			FileIO::WriteColorTextConsole("[WARN] Client version is mismatched with software. Be careful when proceeding...\n", FOREGROUND_RED);
			this->Close();
			ExitThread(0);
		}

		//lots of random vars inits., maybe find way to clean this up
		g_Robot = new AutoPlayer();
		g_Robot->LoopingScript = false;

		//HOOKS AND HACKS INIT
		UINT64 AntiMigrateAddr = gClientBase + g_ProtectionServer->Offsets[11];
		HACK hkAntiMigrate = { AntiMigrateAddr, "\x48\x89\x5C\x24\x08", "\xC3\x90\x90\x90\x90", 5 };
		WriteHackBytes(hkAntiMigrate, TRUE);
		
		UINT64 DumpAddr = gClientBase + g_ProtectionServer->Offsets[4];
		HACK hUploadDump = { DumpAddr, "\x48", "\xC3", 1 };
		WriteHackBytes(hUploadDump, true);

		lpOnSkillGemLevelUpHookFunc = (UINT64)SkillGems::LevelUpSkillGem;
		lpOnSkillGemLevelUpReturnAddr = gClientBase + g_ProtectionServer->Offsets[7] + 6,

		lpClientMessageHookFunc = (UINT64)FileIO::ClientMessageHook;
		lpClientMessageReturnAddr = gClientBase + g_ProtectionServer->Offsets[6] + 5;
		SetHook(gClientBase + g_ProtectionServer->Offsets[6], ClientMessageHook);
		
		UINT64 CPUReduceAddr = gClientBase + (g_ProtectionServer->Offsets[2] - 0x12);
		UINT64 HotkeyHookAddr = gClientBase + (g_ProtectionServer->Offsets[2] - 0x0D);

		lpReduceCPUReturnAddress = CPUReduceAddr + 8;
		//do CPUreducer!

		//InitializeHotkeyVars(HotkeyHookAddr + 8, (UINT64)Hotkey::HandleKeypress);

		//packet hook
		UINT64 OutPacketAddr = gClientBase + g_ProtectionServer->Offsets[0];
		lpSendPacketReturnAddress = (OutPacketAddr + 0x45);
		lpCreatePacketFunc = (UINT64)PacketHelper::CreatePacket;

		lpSendPacketFunction = OutPacketAddr;
		SetHook(OutPacketAddr + 0x3E, OutPacketHook);

		//entity spawn
		lpEntitySpawnReturnAddress = (gClientBase + g_ProtectionServer->Offsets[3] + 0x06);
		lpEntitySpawnFunctionAddress = (UINT64)AutoPlayer::HandleEntitySpawn;
		//SetHook((gClientBase + g_ProtectionServer->Offsets[3]), EntitySpawnHook);

		//labels spawn
		lpEntityLabelSpawnCallbackAddress = (UINT64)AutoPlayer::HandleEntityLabelSpawn;
		lpEntityLabelSpawnReturnAddress = gClientBase + g_ProtectionServer->Offsets[13] + 0x06;
		SetHook((gClientBase + g_ProtectionServer->Offsets[13]), EntityLabelSpawnHook);
		//printf("Hooked EntityLabelSpawnHook\n");
		std::wstring rstr = PacketHelper::randomWStr(9);
		//Hider::ChangeModuleName(L"GoPoE.dll", (wchar_t*)rstr.c_str());
		
		FileIO::WriteColorTextConsole("Welcome to 'GO POE!'\nStatus: Mostly updated\nPlease report any bugs or crashes to the developer!\n", FOREGROUND_GREEN);

		SetConsoleTitleA("OKPoE Console");

		Thread^ IntroThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::Intro));
		IntroThread->Start();

		Random rnd;
		Color randomColor = Color::FromArgb(rnd.Next(256), rnd.Next(256), rnd.Next(256));

		this->BackColor = randomColor;
	}
}


System::Void checkBox_LogSP_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (this->checkBox_LogSP->Checked == true)
	{
		g_Robot->isLoggingOutbound = TRUE;

		OutPacketThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::ProcessSendQueue));
		OutPacketThread->Start();
	}
	else
	{
		for (int i = 0; i < SendPacketQueue.size(); i++)		
			SendPacketQueue.pop();

		g_Robot->isLoggingOutbound = FALSE;
		OutPacketThread->Abort();

	}
}

private: System::Void button_RevealMap_Click(System::Object^  sender, System::EventArgs^  e) {

	g_ProtectionServer->HelloApproved = g_ProtectionServer->SendHWID();

	if (g_ProtectionServer->HelloApproved)
	{
		UINT64 PointerBase = (gClientBase + g_ProtectionServer->Offsets[1]); 

		if (PointerBase != NULL)
		{
			UINT64 PointerTwo = *(UINT64*)PointerBase + Offsets::Pointers::MaphackPtrOfs1;
			if (PointerTwo != NULL)
			{
				UINT64 PointerThree = *(UINT64*)PointerTwo + Offsets::Pointers::RevealMap; 

				if (PointerThree != NULL)
				{
					WritePointer<UINT16>(PointerTwo, Offsets::Pointers::RevealMap, 1);
					Sleep(100);
					WritePointer<UINT16>(PointerTwo, Offsets::Pointers::RevealMap, 0);
				}				
			}
		}
	}
}

private: System::Void button_SendPacket_Click(System::Object^  sender, System::EventArgs^  e) {

	UINT64 SendClass = GetSendClass();

	if (SendClass == NULL)
	{
		FileIO::Log("SendClass was NULL!\n");
		return;
	}

	String^ Pocket = gcnew String(this->textBox_SendPacketInput->Text);

	pin_ptr<const wchar_t> wch = PtrToStringChars(Pocket);
	int len = ((Pocket->Length + 1) * 2);
	char* target = new char[len];
	wcstombs(target, wch, len);
	
	BYTE* Packet = PacketHelper::ToPacketFormat(target); //there could be some problem with this perhaps..
	
	int length = PacketHelper::GetPacketLength(target);
	
	lpSendPacketFunction = gClientBase + g_ProtectionServer->Offsets[0];

	PacketHelper::Send(SendClass, &Packet[0], length); //function frees memory of Packet
}
private: System::Void clearAllToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->listView_Packets ->Items->Clear();
}

private: System::Void copyToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Thread^ newThread = gcnew Thread(gcnew ThreadStart(this, &MainForm::copySendPacket));
	newThread->SetApartmentState(System::Threading::ApartmentState::STA);
	newThread->Start();
}

private: System::Void copySendPacket() 
{
	ListViewItem^ selectedItem;

	for (int i = 0; i < listView_Packets->Items->Count; i++)
	{
		selectedItem = listView_Packets->Items[i];

		if (selectedItem->Selected == true)
		{
			String^ packetString = selectedItem->SubItems[2]->Text;
			Clipboard::SetDataObject(packetString, true);
		}
	}
}


private: System::Void checkBox_RAMReduce_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (this->checkBox_RAMReduce->Checked == true)
	{
		if (g_Robot->haReduceRAM == NULL)
			g_Robot->haReduceRAM = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&ReduceRAM, 0, 0, 0);

	}
	else
	{
		TerminateThread(g_Robot->haReduceRAM, 0);
		g_Robot->haReduceRAM = NULL;
	}

}
private: System::Void checkBox_LogEntity_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (this->checkBox_LogEntity->Checked == true)
	{
		//InitializeEntityHookVars((UINT64)AutoPlayer::HandleEntitySpawn, (gClientBase + g_ProtectionServer->Offsets[3] + 0x06)); //+x10 and x06
		SetHook((gClientBase + g_ProtectionServer->Offsets[3]), EntitySpawnHook);
	}
	else
	{
		RemoveHook(gClientBase + g_ProtectionServer->Offsets[3], 6, (byte*)HookBytes::SpawnOffsetPattern);
	}

}

private: System::Void LogPlayerData()
{
	Entity* LocalPlayer = g_Robot->GetLocalPlayer();
	std::wstring name = Player::GetPlayerName(LocalPlayer);
	SetWindowTextW(FindWindowA("PathOfExile", "Path of Exile"), name.c_str()); //todo: check class name of window, could be null
	delete LocalPlayer;

	while (this->checkBox_DisplayPlayerData->Checked == true)
	{
		Entity* LocalPlayer = g_Robot->GetLocalPlayer();

		uint32_t HP = Life::GetEntityHP(LocalPlayer);
		uint32_t MP = Life::GetEntityMana(LocalPlayer);
		uint32_t ES = Life::GetEntityES(LocalPlayer);

		uint32_t level = Player::GetPlayerLevel(g_Robot->GetLocalPlayer());
		uint32_t exp = Player::GetPlayerExperience(g_Robot->GetLocalPlayer());

		this->label_HP->Text = "HP: " + HP;
		this->label_MP->Text = "MP: " + MP;
		this->label_PlayerES->Text = "Energy Shield: " + ES;

		Vector2 Grid = Positioned::GetGridPosition(LocalPlayer);

		this->label_GridX->Text = "X: " + Grid.X;
		this->label_GridY->Text = "Y: " + Grid.Y;

		this->label_Level->Text = "Level: " + level;
		this->label_Exp->Text = "Experience: " + exp;

		this->label_PlayerClass->Text = "Class: " + Player::GetPlayerClass(LocalPlayer);

		delete LocalPlayer;

		Thread::Sleep(500);
	}

}
private: System::Void checkBox_DisplayPlayerData_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (this->checkBox_DisplayPlayerData->Checked == true)
	{
		PlayerInfoThread = gcnew Thread(gcnew ThreadStart(this, &OKPOE::MainForm::LogPlayerData));
		PlayerInfoThread->SetApartmentState(System::Threading::ApartmentState::STA);
		PlayerInfoThread->Start();
	}
	else
	{
		PlayerInfoThread->Abort();
	}
}



private: System::Void checkBox_AutoFlask_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (this->checkBox_AutoFlask->Checked == true)
	{
		//new thread which checks HP and sends a flask packet at X hp 
		g_Robot->FlaskOnHitpoints = Convert::ToInt32(this->numericUpDown_FlaskHP->Value); //change this with klass vars
		g_Robot->FlaskOnMana = Convert::ToInt32(this->numericUpDown_FlaskMP->Value);
		g_Robot->AutoFlasking = true;

		if (g_Robot->FlaskOnHitpoints > 0 && g_Robot->FlaskOnMana > 0)
		{
			printf("Autoflask at HP: %d\n", g_Robot->FlaskOnHitpoints);
			printf("Autoflask at MP: %d\n", g_Robot->FlaskOnMana);

			g_Robot->Flasker->FlaskerThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&AutoFlask::AutoFlasker, g_Robot->Flasker, 0, 0);
		}
	}
	else
	{
		g_Robot->FlaskOnHitpoints = 0;
		g_Robot->FlaskOnMana = 0;
		g_Robot->AutoFlasking = false;
		TerminateThread(g_Robot->Flasker->FlaskerThread, 0);
	}

}
private: System::Void checkBox_IncreaseLights_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	HACK hkSetLights = { gClientBase + (g_ProtectionServer->Offsets[2]), (char*)HookBytes::LightsOffsetPattern, "\x0F\x28\xF2", 3 };
	WriteHackBytes(hkSetLights, this->checkBox_IncreaseLights->Checked);

}
private: System::Void checkBox_AutoLoot_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (this->checkBox_AutoLoot->Checked)
	{
		if (this->radioButton_AutoLootUseBuiltin->Checked)
		{
			g_Robot->UsingBuiltInItemList = true;
		}
		else if (this->radioButton_AutoLootUseFile->Checked)
		{
			g_Robot->UsingBuiltInItemList = false;
		}

		g_Robot->AutoLooting = true;
		Console::WriteLine("Autoloot: {0}", g_Robot->AutoLooting);

		g_Robot->LootingThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)AutoPlayer::AutolootItems, 0, 0, 0);
	}
	else
	{
		g_Robot->AutoLooting = false;
		
		if(g_Robot->LootingThread != NULL)
			TerminateThread(g_Robot->LootingThread, 0);

		//g_Robot->LootingThread = NULL;
	}

}
private: System::Void creditsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show("Made by Firev2. This is copyrighted software, not intended for distribution.");
}
private: System::Void checkBox_ReduceCPU_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (this->checkBox_ReduceCPU->Checked)
	{
		lpReduceCPUReturnAddress = gClientBase + (g_ProtectionServer->Offsets[2] - 0x15);
		int CPUReducerSleepTime = (int)numericUpDown_CPUReducerTime->Value;
		SetCPUReducerTime(CPUReducerSleepTime);
		printf("Starting CPU Reducer with delay: %d\n", CPUReducerSleepTime);
		SetHook((gClientBase + (g_ProtectionServer->Offsets[2] - 0x1C)), CPUReduceHook);
	}
	else
	{
		RemoveHook(gClientBase + (g_ProtectionServer->Offsets[2] - 0x1C), 5, (byte*)HookBytes::CPUReducerPattern);
	}
}

private: System::Void checkBox_IsTargeting_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (this->checkBox_IsTargeting->Checked)
	{
		try
		{
			String^ skillGemSlot = this->comboBox_SkillGemSlot->Text;
			std::wstring result = msclr::interop::marshal_as<std::wstring>(skillGemSlot);
			unsigned short SkillId = AutoAttacker::GetSkillIdFromSlot(result);

			g_Robot->Attacker->AttackingSkill = SkillId;	
			g_Robot->Attacker->IsHunting = true;
		
			printf("Auto-mob skill selected: %u\n", g_Robot->Attacker->AttackingSkill);

			int jobClass = Player::GetPlayerClass(g_Robot->GetLocalPlayer());

			switch (jobClass)
			{
				case 1: //archers
				case 7:
				case 8:
				case 9:
					g_Robot->AttackDelay = 10;
					break;

				case 2: //marauder
				case 13:
				case 14:
				case 15:
					g_Robot->AttackDelay = 500;
					break;

				case 3: //witch
				case 17:
				case 18:
				case 19:
					g_Robot->AttackDelay = 500;
					break;

				case 4:
				case 20:
				case 21:
				case 22:
					g_Robot->AttackDelay = 500;
					break;

				case 5:
				case 23:
				case 24:
				case 25:
					g_Robot->AttackDelay = 500;
					break;

				case 6: //scion
				case 16:
					g_Robot->AttackDelay = 400;
					break;

				default:
					g_Robot->AttackDelay = 750;
					break;
			};
			
			g_Robot->AutoReviving = true;

			TerminateThread(g_Robot->MonsterHuntingThread, 0);

			skillGemSlot = this->comboBox_MovementSkill->Text;
			result = msclr::interop::marshal_as<std::wstring>(skillGemSlot);
			unsigned short SkillIdMovement = AutoAttacker::GetSkillIdFromSlot(result);

			if (SkillIdMovement > 0)
			{
				g_Robot->Attacker->MovementSkill = SkillIdMovement;
				printf("Movement skill selected: %d\n", SkillIdMovement);
			}

			g_Robot->MonsterHuntingThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) g_Robot->Attacker->HuntingLoop, g_Robot->Attacker, 0, 0);		
		}
		catch (...)
		{
			printf("Bad value entered for skill ID.\n");
		}
	}
	else
	{
		g_Robot->Attacker->IsHunting = false;
		//TerminateThread(g_Robot->HealthMonitorThread, 0);
		TerminateThread(g_Robot->InputThread, 0);
	}

}
private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {

	g_ProtectionServer->HelloApproved = g_ProtectionServer->SendHWID();
	if (g_ProtectionServer->HelloApproved)
	{
		TerminateThread(g_Robot->ScriptingThread, 0); //kills any other running thread to make sure none get executed forever and lost
		String^ scriptText = this->textBox_ScriptText->Text;
		g_Robot->ScriptBuffer = (char*)(void*)Marshal::StringToHGlobalAnsi(scriptText);
		g_Robot->ScriptingThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Scripting::ExecuteLUA, 0, 0, 0);
	}
}
private: System::Void button_LoadLUAScript_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show("This feature is under construction!");
	
}
private: System::Void button_EndScript_Click(System::Object^  sender, System::EventArgs^  e) {

	TerminateThread(g_Robot->ScriptingThread, 0);
	Scripting::StopLUA(g_Robot->LUAController);

}

private: Void SaveFile() {
		
	SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();

	saveFileDialog1->Filter = "LUA files (*.lua)|*.lua";
	saveFileDialog1->FilterIndex = 1;
	saveFileDialog1->RestoreDirectory = true;

	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		System::IO::StreamWriter^ file = gcnew System::IO::StreamWriter(saveFileDialog1->OpenFile());

		// Code to write the stream goes here.
		String^ Script = this->textBox_ScriptText->Text;
		file->Write(Script);
		file->Close();
	}

}

private: System::Void button_SaveLUA_Click(System::Object^  sender, System::EventArgs^  e) {

	Thread^ SaveFileThread = gcnew Thread(gcnew ThreadStart(this, &OKPOE::MainForm::SaveFile));
	SaveFileThread->SetApartmentState(System::Threading::ApartmentState::STA);
	SaveFileThread->Start();

}

private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	g_Robot->isRandomizingScriptName = checkBox_RandomizingLUAName->Checked;

}
private: System::Void checkBox_Follow_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (this->checkBox_Follow->Checked) //after setting to true, our movement hook should pick up anything..
	{
		try
		{
			String^ Name = this->textBox_FollowCharName->Text;
			wchar_t* charName = (wchar_t*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalUni(Name);

			wcscpy(g_Robot->FollowingPlayerName, charName);
				
			String^ skillGemSlot = this->comboBox_FollowMovementSkill->Text;
			std::wstring result = msclr::interop::marshal_as<std::wstring>(skillGemSlot);
			unsigned short SkillId = AutoAttacker::GetSkillIdFromSlot(result);

			if (SkillId > 0)
				g_Robot->FollowPlayerSkill = SkillId;

			g_Robot->IsFollowingActor = true;

			wprintf(L"Waiting to follow: %s\n", g_Robot->FollowingPlayerName);
			wprintf(L"Following will begin when the target player spawns in map or loads within range.\n");

			//start auto follow here?
			if (g_Robot->FollowPlayerThread == NULL) //use a different func to persistantly follow as we wont get inputs
				g_Robot->BeginAutoFollow();
		
		}
		catch (...)
		{
			printf("Bad input for character ID.\n");
			return;
		}
	}
	else
	{
		g_Robot->FollowingUID = 0;
		g_Robot->IsFollowingActor = false;
		TerminateThread(g_Robot->FollowPlayerThread, 0);
		g_Robot->FollowPlayerThread = NULL;
		g_Robot->FollowingPlayer = NULL;
	}
}

private: System::Void button_test_Click(System::Object^  sender, System::EventArgs^  e) {

	Entity* local = g_Robot->GetLocalPlayer();
	g_Robot->LocalPlayer = local;

	printf("Neutral: %d\n", Positioned::IsEntityNeutral(local));

	printf("Action Id: %llX\n", Actor::GetCurrentActionID(local));

	int level = Player::GetPlayerLevel(local);
	printf("Level: %d\n", level);

	long exp = Player::GetPlayerExperience(local);
	printf("Exp: %d\n", exp);

	std::wstring name = Player::GetPlayerName(local);
	wprintf(L"Name: %s\n", name.c_str());

	byte wclass = Player::GetPlayerClass(local);
	wprintf(L"Class (in byte representation): %d\n", wclass);

	Vector2 v = Positioned::GetGridPosition(local);
	printf("Coords: %d, %d\n", v.X, v.Y);

	//delete local;
}
private: System::Void bitcoinToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	MessageBox::Show("Thank you for your interest in OK POE! All donations are greatly appreciated and do not go unnoticed! Please view the Console for additional information such as recipient wallet.");
	FileIO::Log(false, "To donate with bitcoin, please transfer to the following address: bc1q7k65l6cwy26rzmn93szlzp2w0n4jazaqhrzx0e \nYou may add a note/memo if possible with your discord name or HWID if you wish for future goodies!");
}
private: System::Void ethereumToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	MessageBox::Show("Thank you for your interest in OK POE! All donations are greatly appreciated and do not go unnoticed! Please view the Console for additional information such as recipient wallet.");
	FileIO::Log(false, "To donate with Ether, please transfer to the following address: 0xAf3469B17c8EA8d25fa178920600be5E9A1ae310 \nYou may add a note/memo if possible with your discord name or HWID if you wish for future goodies!");
}
private: System::Void payPalToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	MessageBox::Show("Thank you for your interest in OK POE! All donations are greatly appreciated and do not go unnoticed! Please view the Console for additional information such as recipient email.");
	FileIO::Log(false, "Paypal donations can be made using the following link: ");
}
private: System::Void button1_Click_2(System::Object^  sender, System::EventArgs^  e) {

	//ShellExecuteA(0, 0, "https://www.paypal.com/donate?business=LFH5P2T4CBW6A&no_recurring=0&item_name=Donations+towards+OKPOE+software+development.&currency_code=USD", 0, 0, SW_SHOW);
	printf("Currently donations via BTC or ETH are supported. Please select Help -> Become an investor/supporter. Thank you for your interest, even if you don't end up donating!\n");
}

private: System::Void updateCheckToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	MessageBox::Show("This is not yet supported, and will likely be implemented after BETA or when main functionality is done. Thanks for the interest!");
}
private: System::Void numericUpDown_QuitOnHP_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void hotkeysToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {



}
private: System::Void button_MakeTower_Click(System::Object^  sender, System::EventArgs^  e) {

	int count = 0;

	for each (uint32_t id in g_Robot->BlightFoundationIdList)
	{
		PacketWriter* p = PacketBuilder::CreateBlightTower(id, 0x1A); //1a is fire??
		SendPacket(GetSendClass(), (LPBYTE)p->GetBuffer(), p->GetSize());
		count++;
		g_Robot->BlightFoundationIdList.pop_front();
		printf("Deployed tower %d..\n", count);
		Thread::Sleep(250);
	}

	printf("Deployed %d towers total!\n", count);
}

private: System::Void button_AddIgnoredEntity_Click(System::Object^  sender, System::EventArgs^  e) {

	String^ EntityPath = this->textBox_IgnoreEntity->Text;
	wchar_t* Path = (wchar_t*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalUni(EntityPath);

	if (Path != NULL)
	{
		wprintf(L"Ignoring entity with path: %s\n", Path);
		g_Robot->IgnoredEntities.push_back(Path);
	}
}
private: System::Void checkBox_EnterAreaTransitions_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (checkBox_EnterAreaTransitions->Checked == true) //todo: make some thread which checks your x,y vs any area transitions, if within range it enters
	{
		g_Robot->isAutoEnteringAreaTransition = true;
	}
	else
	{
		g_Robot->isAutoEnteringAreaTransition = false;
	}
}


private: System::Void checkBox_AutoRevive_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	bool inTown = radioButton_ReviveTown->Checked;

	if (checkBox_AutoRevive->Checked) //use flask thread or make new hp monitoring...
	{
		if (inTown)
		{
			g_Robot->ReviveInSameMap = false;
		}
		else
		{
			g_Robot->ReviveInSameMap = true;
		}

		g_Robot->AutoReviving = true;
	}
	else 
	{
		printf("Reviving: OFF\n");
		TerminateThread(g_Robot->HealthMonitorThread, 0);
	}

}
private: System::Void checkBox_Hotkeys_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	g_Robot->HotkeysEnabled = checkBox_Hotkeys->Checked;

	if (checkBox_Hotkeys->Checked)
	{
		printf("[OKPOE LOG] Hotkeys: Enabled\n");
		SetHook((gClientBase + (g_ProtectionServer->Offsets[2] - 0x0D)), HotkeyHook);
	}
	else
	{
		printf("[OKPOE LOG] Hotkeys: Disabled\n");
		RemoveHook(gClientBase + (g_ProtectionServer->Offsets[2] - 0x0D), 8, (BYTE*)"\x48\x8D\x84\x24\x98\x00\x00\x00");
	}
}
private: System::Void button1_Click_3(System::Object^  sender, System::EventArgs^  e) {

	FileIO::Log("======= HOTKEY FUNCTIONALITIES =========\n");
	FileIO::Log("F1: Dynamite hack toggler\n");
	FileIO::Log("F2: Execute script in scripting area\n");
	FileIO::Log("F3: Reveal Map\n");
	FileIO::Log("F4: Loot Nearby Items\n");
	FileIO::Log("F5: Toggle CPU Reducer\n");
	FileIO::Log("F6: Toggle RAM Reducer\n");
	FileIO::Log("F7: \n");
	FileIO::Log("F8: \n");
	FileIO::Log("F9: \n");
	FileIO::Log("F10: \n");
	FileIO::Log("F11: \n");
	FileIO::Log("F12: Exit Game\n");
}
private: System::Void checkBox_LevelSkillGems_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (checkBox_LevelSkillGems->Checked)
	{
		SetHook(gClientBase + g_ProtectionServer->Offsets[7], OnSkillGemLevelUpHook);
	}
	else
	{
		RemoveHook(gClientBase + g_ProtectionServer->Offsets[7], 5, (BYTE*)HookBytes::LevelUpSkillGemPattern);
	}
}
private: System::Void checkBox_HookClientMsg_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (checkBox_HookClientMsg->Checked)
	{
		SetHook(gClientBase + g_ProtectionServer->Offsets[6], ClientMessageHook);
	}
	else
	{
		RemoveHook(gClientBase + g_ProtectionServer->Offsets[6], 5, (BYTE*)"\x48\x89\x5C\x24\x08"); //change bytes later
	}
}
private: System::Void checkBox_MuteConsole_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	g_Robot->EntityMsgsSupressed = this->checkBox_MuteConsole->Checked;
}

private: System::Void checkBox_DebugMode_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	g_Robot->DebugMode = checkBox_DebugMode->Checked;
}
private: System::Void button_StopLUA_Click(System::Object^  sender, System::EventArgs^  e) {
	Scripting::StopLUA(g_Robot->LUAController);
}
private: System::Void checkBox_TradeBot_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	g_Robot->AutoTrade->IsSelling = false;
	g_Robot->AutoTrade->IsBuying = false;
	g_Robot->AutoTrade->IsInTrade = false;

	if (checkBox_TradeBot->Checked)
	{
		g_Robot->AutoTrading = true;

		String^ server = comboBox_AutoTradeServer->Text;
		g_Robot->AutoTrade->server = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(server);

		if (radioButton_AutoSell->Checked)
		{
			g_Robot->AutoTrade->IsSelling = true;
			g_Robot->EntityMsgsSupressed = true; //turn off spammy msgs
			g_Robot->AutoTrading = true;

			printf("AutoTrading ON\n");
		}
		else if (radioButton_AutoBuy->Checked) //the harder part
		{
			g_Robot->AutoTrade->IsBuying = true;
			g_Robot->AutoTrade->TheirItemName = (wchar_t*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalUni(textBox_AutoBuyItemName->Text);
		}
	}
	else
	{
		g_Robot->AutoTrading = false;
		g_Robot->AutoTrade->IsSelling = false;
		g_Robot->AutoTrade->IsBuying = false;
	}

}

private: System::Void fineprintToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	printf("For any options labelled with a *, additional information exists related to its functionality.\n\n");
	printf("Swap/Tele hideout currently only supports Cartographer's Hideout. If you use a hideout other than Cartographer's, the decoration layout will be lost, please make sure to save your hideout before using swap hideout if you wish to retain the decorations. More hideouts will be added with time.\n");

}
private: System::Void checkBox_LogHoveredElements_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (checkBox_LogHoveredElements->Checked)
	{
		//...or write hook here, ptr is safer however
		g_Robot->ElementLoggerThread = CreateThread(0,0, (LPTHREAD_START_ROUTINE)Element::PrintHoveredElements, 0, 0, 0);
	}
	else
	{
		TerminateThread(g_Robot->ElementLoggerThread, 0);
	}
}
private: System::Void checkBox_IsSkillMelee_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	g_Robot->Attacker->IsMelee = checkBox_IsSkillMelee->Checked;

}

private: System::Void checkBox_Dynamite_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (this->checkBox_Dynamite->Checked)
	{
		printf("[OKPOE] DynamiteHack = ON\n");
		g_Robot->UsingDynamiteHack = true;
	}
	else
	{
		printf("[OKPOE] DynamiteHack = OFF\n");
		g_Robot->UsingDynamiteHack = false;
	}
}

private: System::Void OpenFile() {

	OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();

	openFileDialog->Filter = "LUA files (*.lua)|*.lua";
	openFileDialog->FilterIndex = 1;
	openFileDialog->RestoreDirectory = true;

	if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		System::IO::StreamReader^ file = gcnew System::IO::StreamReader(openFileDialog->OpenFile());
		textBox_ScriptText->Text = file->ReadToEnd();
		file->Close();
	}

}

private: System::Void button_LoadLUA_Click(System::Object^  sender, System::EventArgs^  e) {

	Thread^ openFileThread = gcnew Thread(gcnew ThreadStart(this, &OKPOE::MainForm::OpenFile));
	openFileThread->SetApartmentState(System::Threading::ApartmentState::STA);
	openFileThread->Start();
}

private: System::Void checkBox_RepeatScript_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	g_Robot->LoopingScript = checkBox_RepeatScript->Checked;
}
private: System::Void checkBox_AutoFlask50_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	g_Robot->UsingFlasksAt50Percent = checkBox_AutoFlask50->Checked;

}


private: System::Void button_DownloadLUA_Click(System::Object^  sender, System::EventArgs^  e) {


}

private: System::Void SetFormControlsLanguge(Languages SelectedLanguage)
{
	if (SelectedLanguage == Languages::EN)
	{
		button_RevealMap->Text = L"Reveal Map Once (F3)";

		checkBox_Follow->Text = L"Auto-Follow";
		checkBox_AutoLoot->Text = L"Autoloot";
		checkBox_IsTargeting->Text = L"Target Nearby Monsters";
	}
	else if (SelectedLanguage == Languages::CN)
	{
		button_RevealMap->Text = L"查看地图完整";
		checkBox_VaalSkill->Text = L"技能 VAAL";
		checkBox_Follow->Text = L"跟随";
		checkBox_AutoLoot->Text = L"自动掠夺";
		checkBox_ReduceCPU->Text = L"更少的 CPU";
		checkBox_RAMReduce->Text = L"更少的 RAM";
		checkBox_IsTargeting->Text = L"攻击生物";
		checkBox_IncreaseLights->Text = L"强光";
		checkBox_MapHack->Text = L"始终完整地图显示";
		checkBox_HookClientMsg->Text = L"客户端机密消息";
		checkBox_LogHoveredElements->Text = L"控制台显示 UI 元素";
		checkBox_Dynamite->Text = L"用炸药代替技能";
		checkBox_AutoFlask->Text = L"开始魔药";
		checkBox_AutoFlask50->Text = L"50% 的药水";
		
		groupBox_Entities->Text = L"对象";
		checkBox_LogEntity->Text = L"跟踪对象";
		checkBox_MuteConsole->Text = L"静默文本";

	}
	else if (SelectedLanguage == Languages::RU)
	{

	}
}

private: System::Void chineseCNToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->SelectedLanguage = Languages::CN;
	SetFormControlsLanguge(this->SelectedLanguage);
}

private: System::Void englishENToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->SelectedLanguage = Languages::EN;
	SetFormControlsLanguge(this->SelectedLanguage);
}
private: System::Void russianRUToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	this->SelectedLanguage = Languages::RU;
	SetFormControlsLanguge(this->SelectedLanguage);
}
private: System::Void checkBox_CraftExploit_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (checkBox_CraftExploit->Checked)
	{
		g_Robot->LoggingHarvestExtractors = true;
	}
	else
	{
		g_Robot->LoggingHarvestExtractors = false;
	}
}
private: System::Void checkBox_MapHack_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	HACK hReveal = { gClientBase + Offsets::Hacks::MaphackAddress, "\x66\xC7\x47\x58\x00\x00", "\x66\xC7\x47\x58\x00\x01", 5 };

	if (this->checkBox_MapHack->Checked)
	{
		WriteHackBytes(hReveal, true);
	}
	else
	{
		WriteHackBytes(hReveal, false);
	}
}
private: System::Void checkBox_VaalSkill_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	g_Robot->Attacker->UsingVaalSkill = checkBox_VaalSkill->Checked;
}
private: System::Void comboBox_MovementSkill_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

	String^ skillGemSlot = this->comboBox_MovementSkill->Text;

	std::wstring result = msclr::interop::marshal_as<std::wstring>(skillGemSlot);
	unsigned short SkillId = AutoAttacker::GetSkillIdFromSlot(result);

	if (SkillId > 0)
	{
		g_Robot->Attacker->MovementSkill = SkillId;
		printf("Movement skill id selected: %d\n", g_Robot->Attacker->MovementSkill);
	}

}
private: System::Void comboBox_PortalGemSlot_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {

	String^ skillGemSlot = this->comboBox_PortalGemSlot->Text;
	std::wstring result = msclr::interop::marshal_as<std::wstring>(skillGemSlot);
	unsigned short skillId = AutoAttacker::GetSkillIdFromSlot(result);

	if (skillId > 0)
	{
		g_Robot->Attacker->PortalSkill = skillId;
		printf("Portal skill id selected: %d\n", g_Robot->Attacker->PortalSkill);
	}

}
private: System::Void comboBox_SkillGemSlot_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	
	UINT16 SkillId = 0;

	String^ skillGemSlot = this->comboBox_SkillGemSlot->Text;
	std::wstring result = msclr::interop::marshal_as<std::wstring>(skillGemSlot);
	unsigned short skillId = AutoAttacker::GetSkillIdFromSlot(result);

	if (skillId > 0)
	{
		g_Robot->Attacker->AttackingSkill = skillId;
		printf("Attacking skill id selected: %d\n", g_Robot->Attacker->AttackingSkill);
	}
}

private: System::Void button_UnloadDLL_Click(System::Object^  sender, System::EventArgs^  e) {

	FreeLibraryAndExitThread(g_OurModule, 0);
}
private: System::Void checkBox_UsingTotems_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	g_Robot->Attacker->UsingTotems = checkBox_UsingTotems->Checked;


}

private: System::Void checkBox_ShowHPBars_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	HACK hBars = { gClientBase + Offsets::Hacks::AlwaysShowLifeBars, "\x7C", "\xEB", 1 };

	if (this->checkBox_ShowHPBars->Checked)
	{
		WriteHackBytes(hBars, true);
		printf("[OKPOE LOG] Enemy HP Bars = always show\n");
	}
	else
	{
		WriteHackBytes(hBars, false);
		printf("[OKPOE LOG] Enemy HP Bars = always show\n");
	}
}
private: System::Void checkBox_Zoom_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	gClientBase = (UINT64)GetModuleHandleA("PathOfExile.exe");

	HACK hZoom = { (gClientBase + g_ProtectionServer->Offsets[9]), "\x0F \x2F \x11", "\x90\x90\x90", 3 };

	if (this->checkBox_Zoom->Checked)
	{
		WriteHackBytes(hZoom, true);
		printf("[OKPOE LOG] No zoom limits enabled. \n");
	}
	else
	{
		WriteHackBytes(hZoom, false);
		printf("[OKPOE LOG] No zoom limits disabled. \n");
	}
}
private: System::Void checkBox_NullTerrain_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (checkBox_NullTerrain->Checked) //this should actually be able to notice some change in cpu/ram, not just visual
	{
		printf("[OKPOE INFO] NULL Terrain not yet implemented, check back soon!\n");
	}
	else
	{

	}
}
private: System::Void checkBox_RighteousFire_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	g_Robot->Attacker->UsingRighteousFire = checkBox_RighteousFire->Checked;
}

private: System::Void checkBox_IsRangedSkill_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (g_Robot->Attacker != NULL)
		g_Robot->Attacker->IsSkillRanged = checkBox_IsRangedSkill->Checked;

}
private: System::Void checkBox_RecordMovement_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (checkBox_RecordMovement->Checked)
	{
		g_Robot->isRecordingMovement = true;
	}
	else
	{
		g_Robot->isRecordingMovement = false;
	}
}
private: System::Void button_PlayBackMovements_Click(System::Object^  sender, System::EventArgs^  e) {

	auto playbackThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)g_Robot->PlayBackMovements, 0, 0, 0);
	WaitForSingleObject(playbackThread, INFINITE);
}
private: System::Void checkBox_LogEntityLabels_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	if (checkBox_LogEntityLabels->Checked)
	{
		SetHook((gClientBase + g_ProtectionServer->Offsets[13]), EntityLabelSpawnHook);
	}
	else
	{
		RemoveHook(gClientBase + g_ProtectionServer->Offsets[13], 5, (byte*)HookBytes::LabelSpawnOffsetPattern);
	}
}
private: System::Void listView_Packets_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) { //send packet to advanced view! yay!
		
			 ListViewItem^ selectedItem;

			 for (int i = 0; i < listView_Packets->Items->Count; i++)
			 {
				 selectedItem = listView_Packets->Items[i];

				 if (selectedItem->Selected == true)
				 {
					 String^ packetString = selectedItem->SubItems[2]->Text;
					 richTextBox_PacketInspector->Text = packetString;
				 }
			 }
}
private: void ConvertSelectedData(String^ toConvert)
{
	String^ trimmed = toConvert->Replace(" ", "");

	if (trimmed->Length == 0 && toConvert->Length == 0)
		return;

	msclr::interop::marshal_context context;
	std::string standardString = context.marshal_as<std::string>(trimmed); //save this code for re-use, great way to convert stuff

	string cStr = string();
	cStr = "0x";
	cStr += standardString.c_str();

	if (cStr.size() == 0)
		return;

	uint64_t decimalFromHex = std::stoull(cStr, nullptr, 16);

	uint8_t i8 = (byte)decimalFromHex;
	uint16_t i16 = (uint16_t)PacketHelper::changeEndianness16(decimalFromHex);
	uint32_t i32 = (uint32_t)PacketHelper::changeEndianness32(decimalFromHex);

	try
	{
		textBox_8Int->Text = Convert::ToString(i8); // str_i8;
		textBox_16Int->Text = Convert::ToString(i16);
		textBox_32Int->Text = Convert::ToString(i32);
		textBox_64Int->Text = Convert::ToString(decimalFromHex);

		string strFromHex = PacketHelper::hex_to_string(standardString);
		textBox_ConvStr->Text = gcnew String(strFromHex.c_str());

	}
	catch (...)
	{
		printf("Conversion failure!\n");
	}

}

private: System::Void richTextBox_PacketInspector_SelectionChanged(System::Object^  sender, System::EventArgs^  e) {
			 
	String^ selected = richTextBox_PacketInspector->SelectedText;
	printf("%s\n", selected);
	
	ConvertSelectedData(selected);

}
private: System::Void saveProfileAsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBoxA(0, "Profiles coming soon...", 0, 0);
}
private: System::Void loadProfileToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	MessageBoxA(0, "Profiles coming soon...", 0, 0);
}

private: System::Void MainForm_Click(System::Object^ sender, System::EventArgs^ e) {
	//stop from throwing ridiculous "unhandled exception"  at System.Windows.Forms.ListView.WndProc(Message& m), ystem.NullReferenceException: Object reference not set to an instance of an object.
}
private: System::Void checkBox_TrialHelper_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

	if (checkBox_TrialHelper->Checked)
	{
		printf("Starting trial helper, make sure entity logging is enabled...\n");
		HANDLE t = g_Robot->GameHelper->GetThread();
		t = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)TaskHelper::AutoClickSwitches, 0, 0, 0);
	}
	else
	{
		TerminateThread(g_Robot->GameHelper->GetThread(), 0);
	}

}
};
}