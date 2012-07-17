//
// LSMIPC
//

// Version guideline: YYYYMMDD
// Add lettering to the end to indicate a new version on the same date, such as 20060305a, 20060305b, etc
// You can also use a standard version numbering system such as 1.00, 1.01, etc. 
// Be aware that for the versioning system, this text is simply compared to another version text from the 
// same extension to check for new versions -- if this version text comes before the compared text (in a 
// dictionary), then an update is available.  Equal text means the version is up to date.  After means this 
// is newer than the compared version.  With that said, use whatever version numbering system you'd like.
#define MODULE_VERSION "20120717"

#include "LSMIPC.h"
#pragma comment(lib,"LSModule.lib")
// The mandatory pre-setup function.  Our name is "LSMIPC", and the class is LSMIPC.
// This sets up a "ModulePath" variable which contains the path to this module in case we want it,
// and a "PluginLog" variable, which contains the path and filename of what we should use for our
// debug logging if we need it.  It also sets up a variable "pExtension" which is the pointer to
// our instanced class.
LSModulePreSetup("LSMIPC",LSMIPC);

// Basic LavishScript datatypes, these get retrieved on startup by our initialize function, so we can
// use them in our Top-Level Objects or custom datatypes
LSTypeDefinition *pStringType=0;
LSTypeDefinition *pIntType=0;
LSTypeDefinition *pUintType=0;
LSTypeDefinition *pBoolType=0;
LSTypeDefinition *pFloatType=0;
LSTypeDefinition *pTimeType=0;
LSTypeDefinition *pByteType=0;
LSTypeDefinition *pIntPtrType=0;
LSTypeDefinition *pBoolPtrType=0;
LSTypeDefinition *pFloatPtrType=0;
LSTypeDefinition *pBytePtrType=0;
LSTypeDefinition *pIndexType=0;
LSTypeDefinition *pQueueType=0;
LSTypeDefinition *pSetType=0;
LSTypeDefinition *pCollectionType=0;
LSTypeDefinition *pStackType=0;
LSTypeDefinition *pIteratorType=0;

LSInterface *pLSInterface=0;

char IPC_Version[]=MODULE_VERSION;


// The constructor of our class.  General initialization cannot be done yet, because we're not given
// the pointer to the LavishScript interface until it is ready for us to initialize.  Just set the
// pointer we have to the interface to 0.  Initialize data members, too.
LSMIPC::LSMIPC(void)
{
}

// Free any remaining resources in the destructor.  This is called when the DLL is unloaded, but
// LavishScript calls the "Shutdown" function first.  Most, if not all, of the shutdown process should
// be done in Shutdown.
LSMIPC::~LSMIPC(void)
{
}

// Initialize is called by Inner Space when the extension should initialize.
bool LSMIPC::Initialize(LSInterface *p_LSInterface)
{
	pLSInterface=p_LSInterface;
	//RegisterModule();

	// retrieve basic ISData types
	pStringType=pLSInterface->FindLSType("string");
	pIntType=pLSInterface->FindLSType("int");
	pUintType=pLSInterface->FindLSType("uint");
	pBoolType=pLSInterface->FindLSType("bool");
	pFloatType=pLSInterface->FindLSType("float");
	pTimeType=pLSInterface->FindLSType("time");
	pByteType=pLSInterface->FindLSType("byte");
	pIntPtrType=pLSInterface->FindLSType("intptr");
	pBoolPtrType=pLSInterface->FindLSType("boolptr");
	pFloatPtrType=pLSInterface->FindLSType("floatptr");
	pBytePtrType=pLSInterface->FindLSType("byteptr");
	pIndexType=pLSInterface->FindLSType("index");
	pQueueType=pLSInterface->FindLSType("queue");
	pSetType=pLSInterface->FindLSType("set");
	pCollectionType=pLSInterface->FindLSType("collection");
	pStackType=pLSInterface->FindLSType("stack");
	pIteratorType=pLSInterface->FindLSType("iterator");

	RegisterEvents();
	RegisterCommands();
	RegisterAliases();
	RegisterDataTypes();
	RegisterTopLevelObjects();
    RegisterTriggers();

	pLSInterface->AttachEventTarget(pIPCIndexEvent, IPCIndexEvent);

	printf("LSMIPC version %s Loaded",IPC_Version);
	return true;
}

// shutdown sequence
void LSMIPC::Shutdown()
{
	UnRegisterTopLevelObjects();
	UnRegisterDataTypes();
	UnRegisterAliases();
	UnRegisterCommands();
}

void LSMIPC::RegisterCommands()
{
	// add any commands
//	pLSInterface->AddCommand("LSMIPC",CMD_LSMIPC,true,false);
#define COMMAND(name,cmd,parse,hide) pLSInterface->AddCommand(name,cmd,parse,hide);
#include "Commands.h"
#undef COMMAND
}

void LSMIPC::RegisterAliases()
{
	// add any aliases
}

void LSMIPC::RegisterDataTypes()
{
	// add any datatypes
	// pMyType = new MyType;
	// pLSInterface->AddLSType(*pMyType);


#define DATATYPE(_class_,_variable_,_inherits_) {_variable_ = new _class_; pLSInterface->AddLSType(*_variable_); _variable_->SetInheritance(_inherits_);}
#include "DataTypeList.h"
#undef DATATYPE
}

#define EVENT(_eventname_,_variable_) unsigned int _variable_=0
#include "Events.h"
#undef EVENT

void LSMIPC::RegisterEvents()
{
	// Register any events
#define EVENT(_eventname_,_variable_) _variable_=pLSInterface->RegisterEvent(_eventname_)
#include "Events.h"
#undef EVENT
}

void LSMIPC::RegisterTopLevelObjects()
{
	// add any Top-Level Objects
	//pLSInterface->AddTopLevelObject("LSMIPC",TLO_LSMIPC);
#define TOPLEVELOBJECT(name,funcname) pLSInterface->AddTopLevelObject(name,funcname);
#include "TopLevelObjects.h"
#undef TOPLEVELOBJECT
}

void LSMIPC::RegisterTriggers()
{
	// add any Triggers
}

void LSMIPC::UnRegisterCommands()
{
	// remove commands
//	pLSInterface->RemoveCommand("LSMIPC");
#define COMMAND(name,cmd,parse,hide) pLSInterface->RemoveCommand(name);
#include "Commands.h"
#undef COMMAND
}
void LSMIPC::UnRegisterAliases()
{
	// remove aliases
}
void LSMIPC::UnRegisterDataTypes()
{
	// remove data types
#define DATATYPE(_class_,_variable_,_inherits_) {pLSInterface->RemoveLSType(*_variable_); delete _variable_;}
#include "DataTypeList.h"
#undef DATATYPE

}
void LSMIPC::UnRegisterTopLevelObjects()
{
	// remove Top-Level Objects
//	pLSInterface->RemoveTopLevelObject("LSMIPC");
#define TOPLEVELOBJECT(name,funcname) pLSInterface->RemoveTopLevelObject(name);
#include "TopLevelObjects.h"
#undef TOPLEVELOBJECT
}


