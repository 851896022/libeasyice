/*
MIT License

Copyright  (c) 2009-2019 easyice

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "tr101290_defs.h"



class CDemux;
class CSysClock;
class CTrCore
{
public:
	CTrCore(void);
	~CTrCore(void);


	void SetTsLen(int nLen);

	//the size must eq to LV3_DATA_DELAY_ERROR+1  Ĭ��ȫ������
	void SetEnable(bool *p);

	//PAT��PMT�Ƿ�������
	bool IsDemuxFinish();

	//������ñ�����������ʼֵ
	void SetStartOffset(long long llOffset);

	void SetReportCB(pfReportCB pCB,void* pApp);

	//���һ�������õĺ���
	void AddPacket(BYTE* pPacket);

	//�ⲿ����
	//void Report(int level,ERROR_NAME_T errName,int pid,long long llVal,double fVal);
private:
	//void Report(int level,ERROR_NAME_T errName,long long llOffset,int pid,long long llVal,double fVal);

	//������ͬ��������
	void ProcessPacket(BYTE* pPacket);

	/**
	 * @brief ����ͬ��
	 * @return 1 ͬ���ɹ���-1 ͬ��ʧ��
	 */
	int TryToReSync();

private:
	bool* m_pEnable;
	//pfReportCB m_pReportCB;
	//void* m_pApp;
	int m_nTslen;

	BYTE* m_pBuffer;
	int m_nBufferPos;

	//long long m_llOffset;

	//�Ƿ���ͬ��
	bool m_bSynced;

	//��һ��TS��ͬ���ֽ��Ƿ���ȷ
	bool m_bPrevPktSync;

	//for check cc
	unsigned long long* m_pCC;
private:
	CDemux* m_pDemuxer;

//��ǰ��ȫ�ֱ���
private:
	long long m_llOffset;

	void* m_pApp;
	pfReportCB  m_pfReportCB;

//��������õ���
public:
	void Report(int level,ERROR_NAME_T errName,long long llOffset,int pid,long long llVal,double fVal);
	void Report(int level,ERROR_NAME_T errName,int pid,long long llVal,double fVal);
	CSysClock* m_pSysClock;

};
