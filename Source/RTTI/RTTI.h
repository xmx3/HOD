#ifndef RTTI_H_
#define RTTI_H_
#include<string>
#include<vector>
#include"GameObject/Rttis.h"
class RTTI 
{
  public:
    RTTI(const std::string & className);
    RTTI(const std::string & className, const RTTI & baseRTTI);
    RTTI(const std::string & className, int numParents, ...);
    ~RTTI();

    const std::string & getClassName() const { return m_className; }
    bool isExactly(const RTTI & rtti) const { return (this == &rtti); }
    bool derivesFrom (const RTTI & rtti) const;

  private:
    // Prevent copying
    RTTI( const RTTI & obj );
    RTTI & operator=( const RTTI & obj );

    const std::string m_className;

    int           m_numParents;
    const RTTI ** m_pBaseRTTI;
};


#define RTTI_DECL \
    public: \
        virtual const RTTI & getRTTI() const { return rtti; } \
        static const RTTI rtti;

#define RTTI_ROOT_IMPL(name) \
    const RTTI name::rtti(#name); \
	namespace Rttis{ \
		const RTTI & name(){ \
			return name::rtti; \
		} \
	}

#define RTTI_IMPL(name,parent) \
    const RTTI name::rtti(#name, parent::rtti); \
	namespace Rttis{ \
		const RTTI & name(){ \
			return name::rtti; \
		} \
	}
#define RTTI_HEADER_IMPL(name) \
	virtual const RTTI & getRTTI() const { return rtti(); } \
    static const RTTI & rtti(){ \
		static const RTTI rtti(#name); \
		return rtti; \
	}


#endif  // _RTTI_H_

