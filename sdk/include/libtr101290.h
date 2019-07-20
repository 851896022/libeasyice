/*
MIT License

Copyright  (c) 2009-2019 easyice

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� LIBTR101290_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// LIBTR101290_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#ifndef LIBTR101290_H
#define LIBTR101290_H

#include "tr101290_defs.h"



//#ifdef LIBTR101290_EXPORTS
//#define LIBTR101290_API __declspec(dllexport)
//#else
//#define LIBTR101290_API __declspec(dllimport)
//#endif


/*
 report ˵��

 ------------------------------------------------
 LV1_PID_ERROR
 pid

 ------------------------------------------------
 LV2_PCR_REPETITION_ERROR
 llVal ������ֵ�������壬��λΪ27mϵͳʱ��
 (int)fVal ����discontinuity_indicator

 ------------------------------------------------
 LV2_PCR_ACCURACY_ERROR
 llVal ������ֵ�������壬��λΪ27mϵͳʱ��

 ------------------------------------------------
 LV2_CRC_ERROR


 ------------------------------------------------
 LV3_PSI_INTERVAL_XXX
 llVal  ������,��λ ms


 ------------------------------------------------
 LV3_NIT_ACTUAL_ERROR_TID
 pid

 ------------------------------------------------
 LV3_PF_ERROR
 pid

 ------------------------------------------------
 LV3_UNREFERENCED_PID
 pid


------------------------------------------------
LV1_PAT_ERROR_OCC
LV1_PMT_ERROR_OCC
llVal()








 ------------------------------------------------
 ��������£�llVal��fVal ���� -1 ��ʾû������




*/


class CTrCore;


// �����Ǵ� libtr101290.dll ������

//ÿ���ļ���Ӧһ���µ������,�ر��ļ�ʱdelete����ʱ������һ��
class  Clibtr101290 {
public:
	Clibtr101290(void);
	~Clibtr101290(void);

	//PAT��PMT�Ƿ�������
	bool IsDemuxFinish();

	void SetReportCB(pfReportCB pCB,void* pApp);

	void SetStartOffset(long long llOffset);

	void SetTsLen(int nLen);

	//the size must eq to LV3_DATA_DELAY_ERROR+1  Ĭ��ȫ������
	void SetEnable(bool *p);

	//���һ�������õĺ���
	void AddPacket(BYTE* pPacket);
private:
	CTrCore* m_pTrCore;
};



extern  int nlibtr101290;




 int fnlibtr101290(void);



#endif

