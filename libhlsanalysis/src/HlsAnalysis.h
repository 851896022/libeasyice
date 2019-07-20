/*
MIT License

Copyright  (c) 2009-2019 easyice

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� HLSANALYSIS_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// HLSANALYSIS_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#ifndef HLS_ANALYSIS_H
#define HLS_ANALYSIS_H


#include "sdkdefs.h"
#include "hls_define.h"










class CHlsAnalysisImpl;

// �����Ǵ� HlsAnalysis.dll ������ ÿ�������Ӧһ�������������
class CHlsAnalysis {
public:
	CHlsAnalysis(void);
	~CHlsAnalysis();


    //�ɹ����� 0 �����򷵻ط���ֵ
    int OpenMRL(EASYICE* handle);

	//�ͷ���Դ��ʧ�ܷ���false
	bool Stop(bool bForce = false); 


	//��ȡ��ǰ�������ݿɲ��ŵ�ʱ��
	bool GetBufferDuration(double& duration,long long& llCurTime);


	void SetProxy(const char* strProxy);
	/***********************for record****************************/

	//��ʼ¼������,�ɹ�����0��ʧ�ܷ��ط���
	int StartRecord(const char* strFileName);

	//ֹͣ¼������
	void StopRecord();

	void SetRecord(const HLS_RECORD_INIT_PARAM_T& rc_param);

	void SetReportCB(PF_HLS_REPORT_CB pCB,void* pApp);
private:
	CHlsAnalysisImpl* m_pHlsAnalysisImpl;
};







//ֻΪʹ��EasyiceDLL�� ��PIDͳ�ƴ���
//extern void LibHlsAnalysisSetMsgWnd(HWND hwnd);





extern int nHlsAnalysis;













#endif

