#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome, //vaut 0
  Msg_StewReady, //vaut1
  Msg_Goodbye, //vaut 2
  Msg_ComeToSeeMe,
  Msg_BobIsBack
};

inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 0:
    return "HiHoneyImHome"; 

  case 1:
    return "StewReady";

  case 2:
      return "Goodbye";

  case 3:
      return "Comme to see me, Bob is not at home.";

  case 4:
      return "Bob is here, leave the house !";

  default:
    return "Not recognized!";
  }
}

#endif