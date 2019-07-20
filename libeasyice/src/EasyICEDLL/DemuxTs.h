/*
MIT License

Copyright  (c) 2009-2019 easyice

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once
#include "TsPacket.h"
#include "ProgramParser.h"
#include "tables/CAnalyzeTable.h"
#include <map>

using namespace std;
using namespace tables;

//��·ģʽ�µ�program_idֵ
#define SINGLE_MODE_PROG_NUM	-1

class CDemuxTs
{
public:
	CDemuxTs(void);
	~CDemuxTs(void);
public:
	//��ʼ���⸴������Ԥ����һ�λ�������ts�⸴��
	/**
		@brif �Ӹ��������н�����Ŀ��pid��Ϣ.�����浽m_vecPrograms
		@return �ɹ�����1��ʧ�ܷ���0
	*/
	int SetupDemux(BYTE* pData, int nLength,int nTsLen);

	int SetupDemux(TABLES* tables,int nTsLen);

	//��·����ģʽ
	void SetupDemux(int VideoPID,int VideoStreamType,int nTsLen);

	//���ý��������Ϣ�洢����
	void SetOutputBuffer(ALL_PROGRAM_INFO* p);

	//���յ���ts�����д���
	PARSED_FRAME_INFO AddTsPacket(CTsPacket* tsPacket);

	//����һ��TS��
	int DecodePacket(BYTE *pPacket, int nLen);
private:
	//��·��Ŀpid��Ϣ ��Ŀ�ţ���Ŀ��Ϣ
	map<int,PROGRAM_PIDS> m_mapProgPids;

	//ÿ·��Ŀ�����Ӧ�Ĵ�����,��Ŀ�ţ�������
	//��Ŀ��=-1 ��ʾ��·����ģʽ
	map<int,CProgramParser*> m_mapProgParser;

	//���н�Ŀ����Ϣ
	ALL_PROGRAM_INFO *m_allProgramInfo;

	bool m_bSingleMode;

	//��ID����¼�������������ݵĵڼ�����������264�﷨ʱ���õ�
	long long m_llPacketID;
};
