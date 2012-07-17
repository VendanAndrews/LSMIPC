#ifndef DATATYPE
#define DATATYPE_SELF
#define DATATYPE(_class_,_variable_,_inherits_) extern class _class_ *_variable_
#endif
// ----------------------------------------------------
// data types

// sample data type is the IPCFooType class, and we're making a variable called pIPCFooType.
// this type does not inherit from another type, so we use 0.  If it did inherit from another single type,
// we would use the pointer to the definition of that type, such as pStringType
DATATYPE(IPCIndexType,pIPCIndexType,0);
DATATYPE(IPCQueueType,pIPCQueueType,0);
DATATYPE(IPCSetType,pIPCSetType,0);
DATATYPE(IPCCollectionType,pIPCCollectionType,0);











// ----------------------------------------------------
#ifdef DATATYPE_SELF
#undef DATATYPE_SELF
#undef DATATYPE
#endif