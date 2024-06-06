#include "BaseException.hpp"
#include "nlohmannJSONAdapter.hpp"

template <typename T>
T NlohmannJsonAdapter::getTypeFromReference(json::reference &ref,
                                            std::string funcname) {
  try {
    return ref.get<T>();
  } catch (const json::type_error &e) {
    throw myException(BaseException, funcname,
                      "Не удалось преобразовать поле в тип " +
                          std::string(typeid(T).name()));
  }
}

template <typename T>
T NlohmannJsonAdapter::getTypeAt(json &data, std::string key,
                                 std::string funcname) {
  return getTypeFromReference<T>(getReference(data, key, funcname), funcname);
}
