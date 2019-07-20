/*
MIT License

Copyright  (c) 2009-2019 easyice

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once
#include "sdkdefs.h"
#include "ztypes.h"
#include <stdio.h>
#include "zevent.h"
#include "commondefs.h"


class CMpegDec;
class CLiveSourceBase;
class CCircularBuffer;
class CLivePcrProc;
class CUdpSend;
class Clibtr101290;
class CEiMediaInfo;
class CTrView;

class CLiveAnalysisImpl
{
public:
	CLiveAnalysisImpl(void);
	~CLiveAnalysisImpl(void);
	int OpenMRL(EASYICE* handle);

	//�ͷ���Դ��ʧ�ܷ���false
	bool Stop(bool bForce = false); 

	//��ȡ��ĿժҪ��Ϣ
	ALL_PROGRAM_BRIEF* GetAllProgramBrief();

	//ʵʱ����ʱ����ȡ����
	LST_RATE_INFO_T* LockGetRate();
	void UnlockRate();

	//ʵʱ����ʱ����ȡPCR��Ϣ
	LST_PCR_INFO_T* LockGetPcrInfo(int pcr_pid);
	void UnlockPcrInfo(int pcr_pid);


		//��ʼ¼������
	int StartRecord(const char* strFileName);

	//ֹͣ¼������
	void StopRecord();

private:
	static void OnRecvData(void* pApp,BYTE* pData,int nLen);
	static void* MediaInfoThread(void* lpParam);

	//�����̺߳���
	static void* WorkThread(void* lpParam);
	void WorkFun();
	void ProcessItem(BYTE* pItem,int nSize,long long llTime);

	//¼���̺߳���
	static void* RecordThread(void* lpParam);

    void LiveCallBackPidList();
    void LiveCallBackPsi();
    void LiveCallBackPcr();
    void LiveCallBackRate();
    void LiveCallBackProgramInfoBrief();
    void LiveCallBackTr101290();
private:
	CLiveSourceBase* m_pSource;
	CCircularBuffer* m_pCircularBuffer;

	//�����߳�
	pthread_t m_hThread;
	bool m_bStop;
	int m_nTsLength;

	//ý����Ϣ���
	BYTE* m_pMediaInfoBuffer;
	int m_nMediaInfoBufferLen;
	bool m_bMediaInfoChecked;
	pthread_t m_hMiThread;

	//�Ƿ��ѳ�ʼ����ϣ�ָ�Ƿ��ѽ�����PAT��PMT���õ������н�Ŀ����Ϣ
	bool m_bInited;

	//ָʾ��ʱ�յ���һ������
	long long m_llFirstByteRecvTime;

	//���һ�ε��ûص���ʱ��
	long long m_llCbUpdateTime;

	CMpegDec *m_mpegdec;
	CLivePcrProc *m_pLiveProc;

	//���͵������Թ�vlc����
	//CUdpSend* m_pUdpSend;

	//ָʾ�Ƿ����յ���һ���ֽڵ�����
	bool m_bRecvedFirstByte;

	FILE* m_fpRecordFile;
	pthread_mutex_t m_mutexRecordFp; //��¼���ļ�ָ�����,��֤�ļ�ָ����Ч��

	//¼���߳�
	pthread_t m_hRecordThread;

	//¼�ƻ���
	CCircularBuffer *m_pRecordBuffer;
	pthread_mutex_t m_mutexRecordBuf; //��¼�ƻ���ָ���������֤����ָ�����Ч��,��д������delete���������ܶ���������Ϊ���������Ʊ�֤
	bool m_bStartRecord;

    Clibtr101290* m_pTrcore;
    EASYICE* m_pHandle;
    string m_sMrl;
    ZEvent m_event;

    CEiMediaInfo* m_pEiMediaInfo;
    CTrView* m_pTrView;

    bool m_bWorkThreadValid;
    bool m_bMiThreadValid;
    bool m_bRecordThreadValid;
};
