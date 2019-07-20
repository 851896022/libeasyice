/*
MIT License

Copyright  (c) 2009-2019 easyice

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once
#include "ccalcpcrn1.h"
#include "PcrOj.h"
#include <list>
#include <map>
#include "commondefs.h"

using namespace std;



class CLivePcrProc
{
public:
	typedef struct _PROGRAM_PCR_INFO_T
	{
		_PROGRAM_PCR_INFO_T()
		{
			llpcrPrev = -1;
			pthread_mutex_init(&mutex,NULL);
		}
		~_PROGRAM_PCR_INFO_T()
		{
			pthread_mutex_destroy(&mutex);
		}
		list<PCR_INFO_T> lstPcrInfo;
		pthread_mutex_t mutex;

		CPcrOj pcrOj;
		CCalcPcrN1 pcrAc;
		long long llpcrPrev;
	}PROGRAM_PCR_INFO_T;

public:
	CLivePcrProc(void);
	~CLivePcrProc(void);

	void SetTsLength(int nLen);

	
	//���ü�������ʱ����(ms)
	void SetCalcTsRateIntervalTime(const int* pTime);

	//����PCR PID�����ж�������ö��
	void AddPcrPid(int pid);

	void ProcessBuffer(BYTE* pData,int nLen,long long llTime);

	//��ȡ����,unlock ʱ�����
	LST_RATE_INFO_T* LockGetRate();
	void UnlockRate();

	//��ȡPCR��Ϣ,unlock ʱ�����
	LST_PCR_INFO_T* LockGetPcrInfo(int pcr_pid);
	void UnlockPcrInfo(int pcr_pid);
//	const map<int,CLivePcrProc::PROGRAM_PCR_INFO_T*>& LockGetPcrInfoAll();
//	void UnlockPcrInfoAll();

	//ѡ��pid���Ժ��ٻ�ȡPCR��Ϣʱ�����ٴδ���
	//void SelectPcrPid(int pid);
	//list<PCR_INFO_T>* LockGetPcrInfo();
	//void UnlockPcrInfo();

private:
	map<int,PROGRAM_PCR_INFO_T*> m_mapProgramPcrInfo;

	int m_nTsLength;

	//���ڼ�������
	list<RATE_INFO_T> m_lstRate;
	pthread_mutex_t m_mutexRate;

	int m_nRecvedBytes;
	long long m_llPrevSysClock;
	const int* m_pCalcTsRateIt;	//��������ʱ���ʱ��(ms)

};
