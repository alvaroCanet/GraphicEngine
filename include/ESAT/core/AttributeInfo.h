#ifndef _ATTRIBUTEINFO_H__
#define _ATTRIBUTEINFO_H__

#include <ESAT\core\type_defines.h>
#include <ESAT\core\ptr\Referenced.h>

namespace ESAT {
namespace core {

enum AttributeName {
	AN_Invalid,
	AN_Position,
	AN_Color,
	AN_UV,
	AN_NORMAL,
	AN_MaxName,
};

enum AttributeType {
	AT_INVALID,
	AT_1F,
	AT_2F,
	AT_3F,
	
};

typedef uint32 AttributeMaskType;


class AttributeInfo : public Referenced {

private:

	AttributeMaskType AttributeMask;
	


public:

	uint32 size_of_elements[32];
	uint32 size_[32];
	uint32 stride;
	int index_[32];
	uint32 offset[32];
	uint32 attrib_num;
	char attrib_name[32][50];
	uint32 program;

	AttributeInfo();
	~AttributeInfo(){};
	void ActiveAttribute(int num);
	bool IsCompatible(AttributeMaskType *atributemask_external);
	AttributeMaskType *getAttributeMask();

};

}
}

#endif