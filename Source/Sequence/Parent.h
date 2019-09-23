#ifndef __SEQUENCE_PARENT_H__
#define __SEQUENCE_PARENT_H__

namespace Sequence{
class Child;

class Parent{
public:
	enum Mode{
		MODE_NEW,
		MODE_LOAD,
		MODE_NONE,
	};
	void update();
	Mode mode() const;
	void setMode( Mode );

	static void create();
	static void destroy();
	static Parent* instance();
private:
	Parent();
	~Parent();

	Mode mMode;

	Child* mChild;

	static Parent* mInstance;
};

} //namespace Sequence

#endif
