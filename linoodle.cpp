
#include "windows_library.h"

#if not defined(OODLE_28_API) and not defined(OODLE_26_API)
#define OODLE_28_API
#endif

#if defined(OODLE_28_API)
#include "linoodle_28.h"
#elif defined(OODLE_26_API)
#include "linoodle_26.h"
#endif

OODLE_API_DECLARE(TYPEDEF)

class OodleWrapper {
public:
    OodleWrapper() :
        m_oodleLib(WindowsLibrary::Load(OODLE_DLL_NAME))
    {
        OODLE_API_DECLARE(MEMBER_INIT)
    }

    OODLE_API_DECLARE(MEMBER_METHODS)

private:
    WindowsLibrary m_oodleLib;
    OODLE_API_DECLARE(MEMBER_DECLS)
};

OodleWrapper g_oodleWrapper;

OODLE_API_DECLARE(EXTERN_FUNCS)
