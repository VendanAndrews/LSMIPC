#pragma once
#include "DataTypeList.h"

// custom object type declarations 

/* 
 * IPCIndex is a C++ class we will interface with for our "IPCIndex" object type
 */
class IPCIndex
{
public:
	IPCIndex()
	{
	}
	~IPCIndex()
	{
	}

	LSIndex* Index;
	LSTypeDefinition* Type;
	char SubType[512];

	char IPCName[255];
};

class IPCIndexType : public LSTypeDefinition
{
public:
	// All data members (retrieving data) should be listed in this enumeration
	enum IPCIndexTypeMembers
	{
		Get,
	};
	// All data methods (performing actions on or with the object) should be listed in this enumeration
	enum IPCIndexTypeMethods
	{
		Set,
		Insert,
		Remove,
		Clear,
		SetIPCName,
		GetIterator,
	};

	IPCIndexType() : LSTypeDefinition("IPCIndex")
	{
		/*
		 * Use the TypeMember macro to activate each member, or use AddMember if the name
		 * would conflict with something else in the source code.
		 */

		TypeMember(Get);

		/*
		 * Use the TypeMethod macro to activate each method, or use AddMethod if the name
		 * would conflict with something else in the source code.
		 */
		TypeMethod(Set);
		TypeMethod(Insert);
		TypeMethod(Remove);
		TypeMethod(Clear);
		TypeMethod(SetIPCName);
		TypeMethod(GetIterator);


	}



	/*********************************************************************************************
	 * Basic operations 
	 *
	 */
	
	/* Retrieve some object, a member of an object of this type, using the given arguments */
	virtual bool GetMember(LSOBJECTDATA ObjectData, PLSTYPEMEMBER pMember, int argc, char *argv[], LSOBJECT &Object);

	/* Perform some action on behalf of this object */
	virtual bool GetMethod(LSOBJECTDATA &ObjectData, PLSTYPEMETHOD pMethod, int argc, char *argv[]);

	/* Retrieve some object, an index of an object of this type, using the given arguments */
	virtual int GetIndex(LSOBJECTDATA ObjectData, int argc, char *argv[], LSOBJECT &Object);

	/* Reduce an object of this type to text */
	virtual bool ToText(LSOBJECTDATA ObjectData, char *buf, unsigned int buflen);



	/*********************************************************************************************
	 * Variable initialization and destruction (allows LavishScript variables to be created with this type)
	 *
	 * If variables are not to be supported by the object type, simply return false from the InitVariable
	 * function, or remove the functions below (they will be replaced by the defaults, which do not allow
	 * variables)
	 *
	 */

	/* Initialize an object of this type, potentially with an object sub-type */
    virtual bool InitVariable(LSOBJECTDATA &ObjectData, const char *SubType);

	/* As the second stage of initializing the object, assign the given value(s).  This will
	 * ALWAYS be called immediately after a successful InitVariable, even if no value is given. */
	virtual bool FromText(LSOBJECTDATA &ObjectData, int argc, char *argv[]);

	/* Destroy an object of this type */
	virtual void FreeVariable(LSOBJECTDATA &ObjectData);



	/*********************************************************************************************
	 * Variable type redirection
	 *
	 * In many cases, there is reason to keep a separate datatype for variables, since variables
	 * may be modified.  For example, the string type works on const char *, which would be unsafe
	 * for a LavishScript variable to modify -- the text may be a constant built right into a module.  
	 * The string type redirects variables to the mutablestring type, which works on utf8string *
	 * and inherits the string type (by accessing the const char *).
     */

	/* This function indicates that the variable type is >this< type.  GetVariableType() can also
	   return 0 (NULL) to indicate that variables are not allowed. */
	virtual LSTypeDefinition *GetVariableType()
	{
		return this; /* Redirection example: return pMutableStringType; */
	}


};

class IPCQueue
{
public:
	IPCQueue()
	{
	}
	~IPCQueue()
	{
	}

	LSQueue* Queue;
	LSTypeDefinition* Type;
	char SubType[512];

	char IPCName[255];
};

class IPCQueueType : public LSTypeDefinition
{
public:
	// All data members (retrieving data) should be listed in this enumeration
	enum IPCQueueTypeMembers
	{
		Peek,
	};
	// All data methods (performing actions on or with the object) should be listed in this enumeration
	enum IPCQueueTypeMethods
	{
		Set,
		Queue,
		Dequeue,
		Clear,
		SetIPCName,
		GetIterator,
	};

	IPCQueueType() : LSTypeDefinition("IPCQueue")
	{
		/*
		 * Use the TypeMember macro to activate each member, or use AddMember if the name
		 * would conflict with something else in the source code.
		 */

		TypeMember(Peek);

		/*
		 * Use the TypeMethod macro to activate each method, or use AddMethod if the name
		 * would conflict with something else in the source code.
		 */
		TypeMethod(Set);
		TypeMethod(Queue);
		TypeMethod(Dequeue);
		TypeMethod(Clear);
		TypeMethod(SetIPCName);
		TypeMethod(GetIterator);


	}



	/*********************************************************************************************
	 * Basic operations 
	 *
	 */
	
	/* Retrieve some object, a member of an object of this type, using the given arguments */
	virtual bool GetMember(LSOBJECTDATA ObjectData, PLSTYPEMEMBER pMember, int argc, char *argv[], LSOBJECT &Object);

	/* Perform some action on behalf of this object */
	virtual bool GetMethod(LSOBJECTDATA &ObjectData, PLSTYPEMETHOD pMethod, int argc, char *argv[]);

	/* Retrieve some object, an Queue of an object of this type, using the given arguments */
	virtual int GetQueue(LSOBJECTDATA ObjectData, int argc, char *argv[], LSOBJECT &Object);

	/* Reduce an object of this type to text */
	virtual bool ToText(LSOBJECTDATA ObjectData, char *buf, unsigned int buflen);



	/*********************************************************************************************
	 * Variable initialization and destruction (allows LavishScript variables to be created with this type)
	 *
	 * If variables are not to be supported by the object type, simply return false from the InitVariable
	 * function, or remove the functions below (they will be replaced by the defaults, which do not allow
	 * variables)
	 *
	 */

	/* Initialize an object of this type, potentially with an object sub-type */
    virtual bool InitVariable(LSOBJECTDATA &ObjectData, const char *SubType);

	/* As the second stage of initializing the object, assign the given value(s).  This will
	 * ALWAYS be called immediately after a successful InitVariable, even if no value is given. */
	virtual bool FromText(LSOBJECTDATA &ObjectData, int argc, char *argv[]);

	/* Destroy an object of this type */
	virtual void FreeVariable(LSOBJECTDATA &ObjectData);



	/*********************************************************************************************
	 * Variable type redirection
	 *
	 * In many cases, there is reason to keep a separate datatype for variables, since variables
	 * may be modified.  For example, the string type works on const char *, which would be unsafe
	 * for a LavishScript variable to modify -- the text may be a constant built right into a module.  
	 * The string type redirects variables to the mutablestring type, which works on utf8string *
	 * and inherits the string type (by accessing the const char *).
     */

	/* This function indicates that the variable type is >this< type.  GetVariableType() can also
	   return 0 (NULL) to indicate that variables are not allowed. */
	virtual LSTypeDefinition *GetVariableType()
	{
		return this; /* Redirection example: return pMutableStringType; */
	}


};

class IPCSet
{
public:
	IPCSet()
	{
	}
	~IPCSet()
	{
	}

	LSSet* Set;

	char IPCName[255];
};

class IPCSetType : public LSTypeDefinition
{
public:
	// All data members (retrieving data) should be listed in this enumeration
	enum IPCSetTypeMembers
	{
		Contains,
	};
	// All data methods (performing actions on or with the object) should be listed in this enumeration
	enum IPCSetTypeMethods
	{
		Add,
		Remove,
		Set,
		Clear,
		SetIPCName,
		GetIterator,
	};

	IPCSetType() : LSTypeDefinition("IPCSet")
	{
		/*
		 * Use the TypeMember macro to activate each member, or use AddMember if the name
		 * would conflict with something else in the source code.
		 */

		TypeMember(Contains);

		/*
		 * Use the TypeMethod macro to activate each method, or use AddMethod if the name
		 * would conflict with something else in the source code.
		 */
		TypeMethod(Add);
		TypeMethod(Remove);
		TypeMethod(Set);
		TypeMethod(Clear);
		TypeMethod(SetIPCName);
		TypeMethod(GetIterator);


	}



	/*********************************************************************************************
	 * Basic operations 
	 *
	 */
	
	/* Retrieve some object, a member of an object of this type, using the given arguments */
	virtual bool GetMember(LSOBJECTDATA ObjectData, PLSTYPEMEMBER pMember, int argc, char *argv[], LSOBJECT &Object);

	/* Perform some action on behalf of this object */
	virtual bool GetMethod(LSOBJECTDATA &ObjectData, PLSTYPEMETHOD pMethod, int argc, char *argv[]);

	/* Retrieve some object, an Set of an object of this type, using the given arguments */
	virtual int GetSet(LSOBJECTDATA ObjectData, int argc, char *argv[], LSOBJECT &Object);

	/* Reduce an object of this type to text */
	virtual bool ToText(LSOBJECTDATA ObjectData, char *buf, unsigned int buflen);



	/*********************************************************************************************
	 * Variable initialization and destruction (allows LavishScript variables to be created with this type)
	 *
	 * If variables are not to be supported by the object type, simply return false from the InitVariable
	 * function, or remove the functions below (they will be replaced by the defaults, which do not allow
	 * variables)
	 *
	 */

	/* Initialize an object of this type, potentially with an object sub-type */
    virtual bool InitVariable(LSOBJECTDATA &ObjectData, const char *SubType);

	/* As the second stage of initializing the object, assign the given value(s).  This will
	 * ALWAYS be called immediately after a successful InitVariable, even if no value is given. */
	virtual bool FromText(LSOBJECTDATA &ObjectData, int argc, char *argv[]);

	/* Destroy an object of this type */
	virtual void FreeVariable(LSOBJECTDATA &ObjectData);



	/*********************************************************************************************
	 * Variable type redirection
	 *
	 * In many cases, there is reason to keep a separate datatype for variables, since variables
	 * may be modified.  For example, the string type works on const char *, which would be unsafe
	 * for a LavishScript variable to modify -- the text may be a constant built right into a module.  
	 * The string type redirects variables to the mutablestring type, which works on utf8string *
	 * and inherits the string type (by accessing the const char *).
     */

	/* This function indicates that the variable type is >this< type.  GetVariableType() can also
	   return 0 (NULL) to indicate that variables are not allowed. */
	virtual LSTypeDefinition *GetVariableType()
	{
		return this; /* Redirection example: return pMutableStringType; */
	}


};

class IPCCollection
{
public:
	IPCCollection()
	{
	}
	~IPCCollection()
	{
	}

	LSObjectCollection* Collection;
	LSTypeDefinition* Type;
	char SubType[512];

	char IPCName[255];
};

class IPCCollectionType : public LSTypeDefinition
{
public:
	// All data members (retrieving data) should be listed in this enumeration
	enum IPCCollectionTypeMembers
	{
		Element,
	};
	// All data methods (performing actions on or with the object) should be listed in this enumeration
	enum IPCCollectionTypeMethods
	{
		Set,
		Erase,
		Clear,
		SetIPCName,
		GetIterator,
	};

	IPCCollectionType() : LSTypeDefinition("IPCCollection")
	{
		/*
		 * Use the TypeMember macro to activate each member, or use AddMember if the name
		 * would conflict with something else in the source code.
		 */

		TypeMember(Element);

		/*
		 * Use the TypeMethod macro to activate each method, or use AddMethod if the name
		 * would conflict with something else in the source code.
		 */
		TypeMethod(Set);
		TypeMethod(Erase);
		TypeMethod(Clear);
		TypeMethod(SetIPCName);
		TypeMethod(GetIterator);


	}



	/*********************************************************************************************
	 * Basic operations 
	 *
	 */
	
	/* Retrieve some object, a member of an object of this type, using the given arguments */
	virtual bool GetMember(LSOBJECTDATA ObjectData, PLSTYPEMEMBER pMember, int argc, char *argv[], LSOBJECT &Object);

	/* Perform some action on behalf of this object */
	virtual bool GetMethod(LSOBJECTDATA &ObjectData, PLSTYPEMETHOD pMethod, int argc, char *argv[]);

	/* Retrieve some object, an Collection of an object of this type, using the given arguments */
	virtual int GetCollection(LSOBJECTDATA ObjectData, int argc, char *argv[], LSOBJECT &Object);

	/* Reduce an object of this type to text */
	virtual bool ToText(LSOBJECTDATA ObjectData, char *buf, unsigned int buflen);



	/*********************************************************************************************
	 * Variable initialization and destruction (allows LavishScript variables to be created with this type)
	 *
	 * If variables are not to be supported by the object type, simply return false from the InitVariable
	 * function, or remove the functions below (they will be replaced by the defaults, which do not allow
	 * variables)
	 *
	 */

	/* Initialize an object of this type, potentially with an object sub-type */
    virtual bool InitVariable(LSOBJECTDATA &ObjectData, const char *SubType);

	/* As the second stage of initializing the object, assign the given value(s).  This will
	 * ALWAYS be called immediately after a successful InitVariable, even if no value is given. */
	virtual bool FromText(LSOBJECTDATA &ObjectData, int argc, char *argv[]);

	/* Destroy an object of this type */
	virtual void FreeVariable(LSOBJECTDATA &ObjectData);



	/*********************************************************************************************
	 * Variable type redirection
	 *
	 * In many cases, there is reason to keep a separate datatype for variables, since variables
	 * may be modified.  For example, the string type works on const char *, which would be unsafe
	 * for a LavishScript variable to modify -- the text may be a constant built right into a module.  
	 * The string type redirects variables to the mutablestring type, which works on utf8string *
	 * and inherits the string type (by accessing the const char *).
     */

	/* This function indicates that the variable type is >this< type.  GetVariableType() can also
	   return 0 (NULL) to indicate that variables are not allowed. */
	virtual LSTypeDefinition *GetVariableType()
	{
		return this; /* Redirection example: return pMutableStringType; */
	}


};

class IPCStack
{
public:
	IPCStack()
	{
	}
	~IPCStack()
	{
	}

	LSStack* Stack;
	LSTypeDefinition* Type;
	char SubType[512];

	char IPCName[255];
};

class IPCStackType : public LSTypeDefinition
{
public:
	// All data members (retrieving data) should be listed in this enumeration
	enum IPCStackTypeMembers
	{
		Top,
	};
	// All data methods (performing actions on or with the object) should be listed in this enumeration
	enum IPCStackTypeMethods
	{
		Set,
		Push,
		Pop,
		Clear,
		SetIPCName,
		GetIterator,
	};

	IPCStackType() : LSTypeDefinition("IPCStack")
	{
		/*
		 * Use the TypeMember macro to activate each member, or use AddMember if the name
		 * would conflict with something else in the source code.
		 */

		TypeMember(Top);

		/*
		 * Use the TypeMethod macro to activate each method, or use AddMethod if the name
		 * would conflict with something else in the source code.
		 */
		TypeMethod(Set);
		TypeMethod(Push);
		TypeMethod(Pop);
		TypeMethod(Clear);
		TypeMethod(SetIPCName);
		TypeMethod(GetIterator);


	}



	/*********************************************************************************************
	 * Basic operations 
	 *
	 */
	
	/* Retrieve some object, a member of an object of this type, using the given arguments */
	virtual bool GetMember(LSOBJECTDATA ObjectData, PLSTYPEMEMBER pMember, int argc, char *argv[], LSOBJECT &Object);

	/* Perform some action on behalf of this object */
	virtual bool GetMethod(LSOBJECTDATA &ObjectData, PLSTYPEMETHOD pMethod, int argc, char *argv[]);

	/* Retrieve some object, an Stack of an object of this type, using the given arguments */
	virtual int GetStack(LSOBJECTDATA ObjectData, int argc, char *argv[], LSOBJECT &Object);

	/* Reduce an object of this type to text */
	virtual bool ToText(LSOBJECTDATA ObjectData, char *buf, unsigned int buflen);



	/*********************************************************************************************
	 * Variable initialization and destruction (allows LavishScript variables to be created with this type)
	 *
	 * If variables are not to be supported by the object type, simply return false from the InitVariable
	 * function, or remove the functions below (they will be replaced by the defaults, which do not allow
	 * variables)
	 *
	 */

	/* Initialize an object of this type, potentially with an object sub-type */
    virtual bool InitVariable(LSOBJECTDATA &ObjectData, const char *SubType);

	/* As the second stage of initializing the object, assign the given value(s).  This will
	 * ALWAYS be called immediately after a successful InitVariable, even if no value is given. */
	virtual bool FromText(LSOBJECTDATA &ObjectData, int argc, char *argv[]);

	/* Destroy an object of this type */
	virtual void FreeVariable(LSOBJECTDATA &ObjectData);



	/*********************************************************************************************
	 * Variable type redirection
	 *
	 * In many cases, there is reason to keep a separate datatype for variables, since variables
	 * may be modified.  For example, the string type works on const char *, which would be unsafe
	 * for a LavishScript variable to modify -- the text may be a constant built right into a module.  
	 * The string type redirects variables to the mutablestring type, which works on utf8string *
	 * and inherits the string type (by accessing the const char *).
     */

	/* This function indicates that the variable type is >this< type.  GetVariableType() can also
	   return 0 (NULL) to indicate that variables are not allowed. */
	virtual LSTypeDefinition *GetVariableType()
	{
		return this; /* Redirection example: return pMutableStringType; */
	}


};
