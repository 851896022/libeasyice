/*
MIT License

Copyright  (c) 2009-2019 easyice

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "global.h"
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

struct timeval hls_analysis::tvnow(void)
{
	/*
	** time() returns the value of time in seconds since the Epoch.
	*/
	struct timeval now;
	now.tv_sec = (long)time(NULL);
	now.tv_usec = 0;
	return now;
}

long long hls_analysis::tvdiff(struct timeval newer, struct timeval older)
{
	return (newer.tv_sec-older.tv_sec)*1000+
		(newer.tv_usec-older.tv_usec)/1000;
}

string hls_analysis::get_uri(const string& url)
{
	if (url.rfind("/") == string::npos)
	{
		return url;
	}
	return url.substr(url.rfind("/")+1);
}



//����ڹ����߳����п����漰������Ϣ������API����ô���������߳���ʹ��WaitForSingleObjectһ�ຯ����������ʹ������ĵķ�����
//Ϊ�˽�������߳���Wait�����⣬΢��ר�������һ������MsgWaitForMultipleObjects��������������Եȴ��źţ�thread,event,mutex�ȵȣ���
//Ҳ���Եȴ���Ϣ��MSG�������������źű�������������Ϣ�������˺��������Է��ء�
//�ο� http://www.cnblogs.com/zhangzhifeng/archive/2011/08/23/2150147.html

void hls_analysis::Ei_MsgWaitForSingleObjects(const pthread_t *pHandles,int dwMilliseconds)
{
    pthread_join(*pHandles,NULL);
	//while(TRUE)
	//{

	//	DWORD result ; 
	//	MSG msg ; 

	//	result = MsgWaitForMultipleObjects(1, pHandles, 
	//	FALSE, dwMilliseconds, QS_ALLINPUT); 

	//	if (result == (WAIT_OBJECT_0))
	//	{
	//		break;
	//	} 
	//	else 
	//	{ 
	//		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	//		DispatchMessage(&msg); 
	//	} 
	//}
}


string hls_analysis::removeparam(const string& filename)
{
        if (filename.length() < 2)
        {
                return "";
        }
        int pos = 0;
        for (; pos < filename.length(); pos++)
        {
                if (filename[pos] == '?' ||
                        filename[pos] == '&')
                {
                        break;
                }
//                 if (!isalpha(filename[pos]))
//                 {
//                         break;
//                 }
        }
        if (pos == filename.length())
        {
                return filename;
        }

        if (pos <= 0)
        {
                return "";
        }
        return filename.substr(0,pos);
}


void hls_analysis::CreateMulPath( const char *muldir )
{
        int    i,len;
        char    str[512];

        strncpy( str, muldir, 512 );
        len=strlen(str);
        //printf( "�ַ���%s����=%d\n", str, len );
        for( i=0; i<len; i++ )
        {
                if( str[i]=='/' )
                {
                        str[i] = '\0';
                        //�жϴ�Ŀ¼�Ƿ����,�������򴴽�
                        if( (access(str, R_OK )) != 0 )
                        {
                                //printf( "������%d��Ŀ¼ p=[%s]\n", i, str );
                                mkdir( str ,0777);
                        }
                        str[i]='/';
                }
        }
        if( len>0 && (access(str, R_OK )) != 0)
        {
                //printf( "���һ��Ŀ¼=%s!!!!!!!\n", str );
                mkdir( str ,0777);
        }
        return;
}



