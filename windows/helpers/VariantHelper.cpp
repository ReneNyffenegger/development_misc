#include "VariantHelper.h"
#include "win32_Unicode.h"

std::string TypeAsString(VARTYPE vt){
  switch (vt) {
    case    VT_EMPTY:
    return "VT_EMPTY";

    case    VT_NULL:
    return "VT_NULL";

    case    VT_I2:
    return "VT_I2";

    case    VT_I4:
    return "VT_I4";

    case    VT_R4:
    return "VT_R4";

    case    VT_R8:
    return "VT_R8";

    case    VT_CY:
    return "VT_CY";

    case    VT_DATE:
    return "VT_DATE";

    case    VT_BSTR:
    return "VT_BSTR";

    case    VT_DISPATCH:
    return "VT_DISPATCH";

    case    VT_ERROR:
    return "VT_ERROR";

    case    VT_BOOL:
    return "VT_BOOL";

    case    VT_VARIANT:
    return "VT_VARIANT";

    case    VT_DECIMAL:
    return "VT_DECIMAL";

    case    VT_RECORD:
    return "VT_RECORD";

    case    VT_UNKNOWN:
    return "VT_UNKNOWN";

    case    VT_I1:
    return "VT_I1";

    case    VT_UI1:
    return "VT_UI1";

    case    VT_UI2:
    return "VT_UI2";

    case    VT_UI4:
    return "VT_UI4";

    case    VT_INT:
    return "VT_INT";

    case    VT_UINT:
    return "VT_UINT";

    case    VT_VOID:
    return "VT_VOID";

    case    VT_HRESULT:
    return "VT_HRESULT";

    case    VT_PTR:
    return "VT_PTR";

    case    VT_SAFEARRAY:
    return "VT_SAFEARRAY";

    case    VT_CARRAY:
    return "VT_CARRAY";

    case    VT_USERDEFINED:
    return "VT_USERDEFINED";

    case    VT_LPSTR:
    return "VT_LPSTR";

    case    VT_LPWSTR:
    return "VT_LPWSTR";

    case    VT_BLOB:
    return "VT_BLOB";

    case    VT_STREAM:
    return "VT_STREAM";

    case    VT_STORAGE:
    return "VT_STORAGE";

    case    VT_STREAMED_OBJECT:
    return "VT_STREAMED_OBJECT";

    case    VT_STORED_OBJECT:
    return "VT_STORED_OBJECT";

    case    VT_BLOB_OBJECT:
    return "VT_BLOB_OBJECT";

    case    VT_CF:  // Clipboard Format
    return "VT_CF";

    case    VT_CLSID:
    return "VT_CLSID";

    case    VT_VECTOR:
    return "VT_VECTOR";

    case    VT_ARRAY:
    return "VT_ARRAY";

    //case    VT_BYREF:
    //return "VT_BYREF";

    case    VT_BYREF|VT_DECIMAL:
    return "VT_BYREF|VT_DECIMAL";


    //case    VT_ARRAY|*:
    //return "VT_ARRAY|*";

    case    VT_BYREF|VT_UI1:
    return "VT_BYREF|VT_UI1";

    case    VT_BYREF|VT_I2:
    return "VT_BYREF|VT_I2";

    case    VT_BYREF|VT_I4:
    return "VT_BYREF|VT_I4";

    case    VT_BYREF|VT_R4:
    return "VT_BYREF|VT_R4";

    case    VT_BYREF|VT_R8:
    return "VT_BYREF|VT_R8";

    case    VT_BYREF|VT_BOOL:
    return "VT_BYREF|VT_BOOL";

    case    VT_BYREF|VT_ERROR:
    return "VT_BYREF|VT_ERROR";

    case    VT_BYREF|VT_CY:
    return "VT_BYREF|VT_CY";

    case    VT_BYREF|VT_DATE:
    return "VT_BYREF|VT_DATE";

    case    VT_BYREF|VT_BSTR:
    return "VT_BYREF|VT_BSTR";

    case    VT_BYREF|VT_UNKNOWN:
    return "VT_BYREF|VT_UNKNOWN";

    case    VT_BYREF|VT_DISPATCH:
    return "VT_BYREF|VT_DISPATCH";

    //case    VT_ARRAY|*:
    //return "VT_ARRAY|*";

    case    VT_BYREF|VT_VARIANT:
    return "VT_BYREF|VT_VARIANT";

       //Generic case ByRef:
    //return "ByRef";


    case    VT_BYREF|VT_I1:
    return "VT_BYREF|VT_I1";

    case    VT_BYREF|VT_UI2:
    return "VT_BYREF|VT_UI2";

    case    VT_BYREF|VT_UI4:
    return "VT_BYREF|VT_UI4";

    case    VT_BYREF|VT_INT:
    return "VT_BYREF|VT_INT";

    case    VT_BYREF|VT_UINT:
    return "VT_BYREF|VT_UINT";

    default:
    return "Unknown type";
  }
}

std::string VariantTypeAsString(const VARIANT& v) {
  return TypeAsString(v.vt);
}

variant::variant(VARIANT v) : v_(v) {
}

variant::~variant() {
  ::VariantClear(&v_);
}

std::string variant::ValueAsString() {
  if (v_.vt != VT_BSTR) {
    variant v = *this;

    v.ChangeType(VT_BSTR);
    return v.ValueAsString();
  }

  return ws2s(v_.bstrVal);
}

void variant::ChangeType(VARTYPE vt) {
  ::VariantChangeType(&v_, &v_, VARIANT_ALPHABOOL, vt);
}

