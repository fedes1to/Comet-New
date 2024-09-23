#pragma once

uintptr_t GameAssembly = (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
DWORD pid;

FORCEINLINE uintptr_t get_offset(uintptr_t offset) {
    return GameAssembly + offset;
}

FORCEINLINE uintptr_t get_offset(void* offset) {
    return GameAssembly + (uintptr_t)offset;
}

#define OFFSET(offset) get_offset(string2Offset(OBFUSTR(offset)))
#define IL2CPP_METHOD(klass, name) IL2CPP::Class::Utils::GetMethodPointer(OBFUSTR(klass), OBFUSTR(name));
#define IL2CPP_METHOD_ARGS(klass, name, argCount) IL2CPP::Class::Utils::GetMethodPointer(OBFUSTR(klass), OBFUSTR(name), OBFUSINT(argCount));

template<typename T> inline T& GetField(void* instance, uint64_t offset) {
    return (T&)(*(T*)((uint64_t)instance + offset));
}

template <typename T>
class Pointer;

template <typename R, typename... Args>
class Pointer<R(Args...)>
{
public:
    Pointer() = default;
    explicit Pointer(uintptr_t offset) {
        m_Function = reinterpret_cast<R(*)(Args...)>(offset);
    }

    explicit Pointer(void* offset) {
        m_Function = reinterpret_cast<R(*)(Args...)>(offset);
    }

    inline Pointer& operator=(uintptr_t offset) {
        m_Function = reinterpret_cast<R(*)(Args...)>(offset);
        return *this;
    }

    inline Pointer& operator=(void* offset) {
        m_Function = reinterpret_cast<R(*)(Args...)>(offset);
        return *this;
    }

    inline uintptr_t Offset() {
        return (uintptr_t)((void*)m_Function);
    }

    inline R operator()(Args... args) {
        return m_Function(std::forward<Args>(args)...);
    }

private:
    R(*m_Function)(Args...);
};