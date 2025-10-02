#ifndef D80D28EE_55F6_43B4_A77B_68B4567840C7
#define D80D28EE_55F6_43B4_A77B_68B4567840C7
class NoCopy
{
public:
    NoCopy(){};
    NoCopy(const NoCopy&) = delete;
    NoCopy& operator=(const NoCopy&) = delete;
};

#endif /* D80D28EE_55F6_43B4_A77B_68B4567840C7 */
