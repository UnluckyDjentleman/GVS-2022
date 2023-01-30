#pragma once
#include "Greibach.h"
#include"LT.h"
#include"Log.h"
#include <stack>
#include<iomanip>
#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3
class MFSTSTSTACK :public std::stack<short> {
public:
	using std::stack<short>::c;
};		///���� ��������
static int FST_TRACE_n = -1;
#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)
static char rbuf[205], sbuf[205], lbuf[1024];
#define MFST_TRACE_START(LOG) *log.stream << std::setw( 4)<<std::left<<"STEP"<<":" \
	<< std::setw(20) << std::left << "RULE"  \
	<< std::setw(30) << std::left << "INPUT CHAIN" \
	<< std::setw(20) << std::left << "STACK" \
	<< std::endl;

#define MFST_TRACE1(LOG) *log.stream <<std::setw(4)<<std::left<<++FST_TRACE_n<<":" \
	<< std::setw(20) << std::left << rule.getCRule(rbuf, nrulechain)  \
	<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position) \
	<< std::setw(20) << std::left << getCSt(sbuf) \
	<< std::endl;

#define MFST_TRACE2(LOG)    *log.stream <<std::setw(4)<<std::left<<FST_TRACE_n<<":" \
	<< std::setw(20) << std::left << " "  \
	<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position) \
	<< std::setw(20) << std::left << getCSt(sbuf) \
	<< std::endl;

#define MFST_TRACE3(LOG)     *log.stream<<std::setw(4)<<std::left<<++FST_TRACE_n<<":" \
	<< std::setw(20) << std::left << " "  \
	<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position) \
	<< std::setw(20) << std::left << getCSt(sbuf) \
	<< std::endl;

#define MFST_TRACE4(LOG, c) *log.stream<<std::setw(4)<<std::left<<++FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<std::endl;
#define MFST_TRACE5(LOG, c) *log.stream<<std::setw(4)<<std::left<<  FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<std::endl;

#define MFST_TRACE6(LOG,c,k) *log.stream<<std::setw(4)<<std::left<<++FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<k<<std::endl;

#define MFST_TRACE7(LOG)  *log.stream<<std::setw(4)<<std::left<<state.lenta_position<<": "\
	<< std::setw(20) << std::left << rule.getCRule(rbuf, state.nrulechain) \
	<< std::endl;
namespace MFST
{
	struct MfstState			//��������� �������� (��� ����������)
	{
		short lenta_position;	///������� �� �����
		short nrule;
		short nrulechain;		///� ���. �������, ���. �������
		MFSTSTSTACK st;			///���� ��������
		MfstState();
		MfstState(
			short pposition,	///������� �� �����
			MFSTSTSTACK pst,	///���� ��������
			short pnrulechain	///� ������� �������, ���. �������
		);
		MfstState(
			short pposition,
			MFSTSTSTACK pst,
			short pnrule,
			short pnrulechain
		);
	};
	class my_stack_MfstState :public std::stack<MfstState> {
	public:
		using std::stack<MfstState>::c;
	};
	struct Mfst					//���������� �������
	{
		enum RC_STEP {			///��� �������� �-� step
			NS_OK,				///0 (������� ������� � �������, ���. �������� � ����)
			NS_NORULE,			///1 (�� ������� ������� (������ � ����������)) 
			NS_NORULECHAIN,		///2 (�� ������� ���������� ������� ������� (������ � ���. ����)
			NS_ERROR,			///3 (����������� ����������)
			TS_OK,				///4 (���. ������ ����� == ������� �����, ������������ �����, pop �����)
			TS_NOK,				///5 (���. ������ ����� != ������� �����, ������������� ���������)
			LENTA_END,			///6 (���. ������� ����� >= lenta_size)
			SURPRISE
		};			///7 (����������� ��� �������� (������ � step)

		struct MfstDiagnosis		//�����������
		{
			short lenta_position;	///������� �� �����
			RC_STEP rc_step;		///��� ���������� ����
			short nrule;			///����� �������
			short nrule_chain;		///����� ������� �������
			MfstDiagnosis();
			MfstDiagnosis(
				short plenta_position,
				RC_STEP prc_step,
				short pnrule,
				short pnrule_chain);
		}diagnosis[MFST_DIAGN_NUMBER];	///��������� ����� �������� ���������

		GRBALPHABET* lenta;		///���������������� (TS/NS) ����� (�� LEX)
		short lenta_position;	///���. ������� �� �����
		short nrule;			///����� ���. �������
		short nrulechain;		///����� ���. �������, ���. �������
		short lenta_size;		///������ �����
		GRB::Greibach grebach;	///��������� �������
		LT::LexTable lex;		///���. ������ ��
		MFSTSTSTACK st;			///���� ��������
		my_stack_MfstState storestate;	///���� ��� ���������� ���������
		Mfst();
		Mfst(
			LT::LexTable& plex,
			GRB::Greibach pgrebach);

		char* getCSt		///�������� ���������� �����
		(
			char* buf
		);
		char* getCLenta		///�����: n �������� � pos
		(
			char* buf,
			short pos,
			short n = 25
		);
		char* getDiagnosis	///�����. n-�� ������ ����������� ��� 0x00
		(
			short n,
			char* buf
		);
		bool savestate(const Log::LOG&log);	///��������� ��������� ��������
		bool reststate(const Log::LOG& log);	///�����. ��������� ��������
		bool push_chain		///��������� ������� ������� � ����
		(
			GRB::Rule::Chain chain	///������� �������
		);
		RC_STEP step(const Log::LOG& log);		///��������� ��� ��������
		bool start(const Log::LOG& log);		///��������� �������
		bool savediagnosis
		(
			RC_STEP pprc_step	///��� ���������� ����
		);
		void printrules(const Log::LOG& log);	///������� ������������������ ������


		struct Deducation	///�����
		{
			short size;				///���-�� ����� � ������
			short* nrules;			///������ ������ ����������
			short* nrulechains;		///������ ������� ������ ���������� (nrules)
			Deducation() {
				size = 0;
				nrules = 0;
				nrulechains = 0;
			};
		}deducation;
		bool savededucation(const Log::LOG& log);		///��������� ������ ������
	};
}