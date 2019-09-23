#pragma once
#include<memory>

namespace MME{ namespace Object{
	class IObject;
	typedef std::shared_ptr<IObject> IObjectSharedPtr;
	typedef std::weak_ptr<IObject> IObjectWeakPtr;
	class PointLight;
	typedef std::shared_ptr<PointLight> PointLightSharedPtr;
	class ModelKai;
	typedef std::shared_ptr<ModelKai> ModelKaiSharedPtr;


} }//MME::Object