
inline int readInt()
{
    int ip = getchar_unlocked(), ret = 0, flag = 1;

    for(; ip < 48 || ip > 57; ip = getchar_unlocked())
    {
        if(ip == 45)
        {
            flag = -1;
            ip = getchar_unlocked();
            break;
        }
    }

    for(; ip > 47 && ip < 58; ip = getchar_unlocked())
        ret = ret * 10 + ip - 48 ;
    return flag * ret;
}








struct Input {
  #define maxBufSize (1 << 23)
  #define maxStrSize (1 << 23)
  int bufSize, bufEnd, bufPos;
  char buffer[maxBufSize];
  void grabBuffer() {
    bufSize = (maxBufSize);
    bufPos = 0;
    bufEnd = fread(buffer, sizeof (char), bufSize, stdin);
    buffer[bufEnd] = '\0';
  }
  bool bufEof() {
    return bufPos == bufEnd;
  }
  int getChar() {
    return buffer[bufPos++];
  }
  void skipWS() {
    while ((buffer[bufPos] == '\n' ||
            buffer[bufPos] == ' ' || buffer[bufPos] == '\t'))
      bufPos++;
  }
  int rUint() {
    int n = 0, x;
    skipWS();
    for (int x = getChar(); x <= '9' && x >= '0'; x = getChar())
      n = (n << 3) + (n << 1) + (x - '0');
    return n;
  }
  int Int() {
    int sign = 0, n = 0, x;
    skipWS();
    if (buffer[bufPos] == '-')
      sign = 1, getChar();
    for (x = getChar(); x <= '9' && x >= '0'; x = getChar())
      n = (n << 3) + (n << 1) + (x - '0');
    return sign == 0? n: -n;
  }
  inline bool isWhiteSpace(char x) {
    return x == ' ' || x == '\n' || x == '\t';
  }
  string rStr() {
    char result[maxStrSize];
    skipWS();
    int idx = 0, x;
    for (x = getChar(); !isWhiteSpace(x); x = getChar())
      result[idx++] = x;
    result[idx] = '\0';
    return result;
  }
  char rChar() {
    skipWS();
    return getChar();
  }
};
