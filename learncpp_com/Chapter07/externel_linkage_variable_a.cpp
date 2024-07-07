// global variable definitions
int g_x{2}; // non-constant globals have external linkage by default
extern const int g_y{3}; // this extern gives g_y external linkage