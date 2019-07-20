/*
MIT License

Copyright  (c) 2009-2019 easyice

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once
#include "TsPacket.h"
#include "H264Dec.h"
#include <iostream>
#include "jmdec.h"

using namespace std;

#define MAXSPS  32
#define MAXPPS  256


///@brief	������·��Ŀ��ͳ��pts��dts��pcr��
class CProgramParser
{
public:
	CProgramParser(int nTsLength);
	~CProgramParser(void);
public:
	/**
	* ��Ҫ��֤�����TS���Ǳ�·��Ŀ�ġ�
	*/
	PARSED_FRAME_INFO PushBackTsPacket(CTsPacket* tsPacket,long long packetID);

	//���ý��������Ϣ�洢����
	void SetOutputBuffer(PROGRAM_INFO* p) { m_pProgInfo = p; }

	//������Ƶpid�������ͣ�Ŀǰ֧�ֽ���ģ�
	void SetVideoStreamInfo(PID_STREAM_TYPE video_pid_type);

	//������Ӱ������ƵPID����֧��1��
	void SetAudioPid(int pid);

	//����һ��TS��
	int DecodePacket(CTsPacket* tsPacket);

	//����һ���Ǳ���ĿPID�İ�
	void AddOtherPacket();
private:
	//���GOP
	void MPEG2_AssembleGop(BYTE bPic);

	void H264_AssembleGop(FRAME_TYPE frame_type);

	//��������
	inline void MakeRate(long long pcr);
private:
	//����Ŀ��TS��������
	unsigned long long m_llTotalPacketCounter;

	//����ʱ�����Ϣ
	

	//��ǰpcr��pts��dts��Ϣ
	long long  m_pcr;
	long long  m_Vpts;
	long long  m_Apts;
	long long  m_dts;

	//���һ��pcrֵ
	//TIMESTAMP m_lastPcrtp;

	//��GOP����ʱ�ַ���
	string m_gopTmp;
	int m_nGopsizeTmp;
	int m_nGopBytesTmp;

	//�洢�������Ľ�Ŀ��Ϣ
	PROGRAM_INFO* m_pProgInfo;


	//��PCR�������
	int m_nPacketCountOfPcr;

	//��һ��PCR
	long long m_pcrBefor;

	//��Ƶpid��������
	PID_STREAM_TYPE m_video_pid_type;

	int m_nAudioPid;

	//H264�﷨������
	CH264Dec m_avcParser;
	

	int m_nTsLength;
private:
	//13818-2 p22 ��������(�ֽ���)
	double m_fTransportRate;

private:

};
