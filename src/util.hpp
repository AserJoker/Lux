#ifndef _H_LUX_UTIL_
#define RUNTIME_ERROR(msg)                                                     \
  std::runtime_error(fmt::format("{} :\n\t at {}:{}", msg, __FILE__, __LINE__))
#define SDL_ERROR RUNTIME_ERROR(SDL_GetError())
#define DEFINE_TOKEN(token) constexpr static const char *TOKEN = #token;

template<size_t N>
struct c_string {
    constexpr c_string(const char (&str)[N]) {
        std::copy_n(str, N, value);
    }
    char value[N];
};
#endif