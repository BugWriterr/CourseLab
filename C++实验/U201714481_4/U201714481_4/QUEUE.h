//#include"STACK.h"


class QUEUE :public STACK {
	STACK  s;
public:
	QUEUE(int m); //ÿ��ջ���m��Ԫ�أ�Ҫ��ʵ�ֵĶ����������2m��Ԫ��
	QUEUE(const QUEUE&q); 			//�ö���q������ʼ������
	QUEUE(QUEUE&&q);				//�ƶ�����
	virtual operator int() const;			//���ض��е�ʵ��Ԫ�ظ���
	virtual int full() const;		       //���ض����Ƿ�������������1������0
	virtual int operator[ ](int x)const;   //ȡ�±�Ϊx��Ԫ�أ���1��Ԫ���±�Ϊ0
	virtual QUEUE& operator<<(int e);  //��e�����,�����ض���
	virtual QUEUE& operator>>(int &e);	//�����е�e,�����ض���
	virtual QUEUE& operator=(const QUEUE&q); //��q������,�����ر���ֵ����
	virtual QUEUE& operator=(QUEUE&&q);  //�ƶ���ֵ
	virtual void print() const;			//��ӡ����
	virtual ~QUEUE();					//���ٶ���
};
