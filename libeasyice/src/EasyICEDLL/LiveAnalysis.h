/*
MIT License

Copyright  (c) 2009-2019 easyice

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "commondefs.h"
#include "sdkdefs.h"



class CLiveAnalysisImpl;
class CLiveAnalysis
{
public:
	CLiveAnalysis(void);
	~CLiveAnalysis(void);

	//�ɹ����� 0 �����򷵻ط���ֵ
	int OpenMRL(EASYICE* handle);

	//�ͷ���Դ��ʧ�ܷ���false
	bool Stop(bool bForce = false); 

	//��ȡ��ĿժҪ��Ϣ
	ALL_PROGRAM_BRIEF* GetAllProgramBrief();

	//ʵʱ����ʱ����ȡ����,��ȡ����÷�Ӧ�������
	LST_RATE_INFO_T* LockGetRate();
	void UnlockRate();

	//ʵʱ����ʱ����ȡPCR��Ϣ����ȡ����÷�Ӧ�������
	LST_PCR_INFO_T* LockGetPcrInfo(int pcr_pid);
	void UnlockPcrInfo(int pcr_pid);

	//���ü�������ʱ����(ms)
//	void SetCalcTsRateIntervalTime(int nTime);

	//��ʼ¼������,�ɹ�����0��ʧ�ܷ��ط���
	int StartRecord(const char* strFileName);

	//ֹͣ¼������
	void StopRecord();
private:
	CLiveAnalysisImpl* m_pLiveAnalysisImpl;
};
