//字符串转int
int char_int(char *p)//将字符串(十进制数)转为int,需要保证p字符串里面是'0'到'9'
{
    char *p2=p+strlen(p);//p2指向'\0'
    int tmp=0;
    int wei=1;//wei是进位从个位开始
    while (p2!=p)
    {
        p2--;
        tmp=tmp+(*p2-48)*wei;
        wei=wei*10;
    }
    return tmp;
}