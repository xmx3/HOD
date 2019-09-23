#ifndef __MAIN_H__
#define __MAIN_H__

#undef max
#undef min
#include <GameLib/Framework.h>
#include <GameLib/DebugScreen.h>
#include <GameLib/Math/Matrix44.h>
#include <GameLib/Math/Matrix34.h>
#include <GameLib/Math/Vector4.h>
#include <GameLib/Math/Vector3.h>
#include <GameLib/Math/Vector2.h>
#undef max
#undef min
#include <GameLib/Math/Functions.h>
#include <GameLib/Scene/PrimitiveRenderer.h>
#include <GameLib/Graphics/Manager.h>
#include <GameLib/Input/Manager.h>
#include <GameLib/Input/Keyboard.h>
#include <GameLib/Input/Mouse.h>

#include "BulletPhysics/Manager.h"
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/timer.hpp>

#include <limits>

#include "helper/PrintBtVector3.h"

#endif