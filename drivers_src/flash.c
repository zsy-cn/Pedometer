 /**
  ******************************************************************************
  * @file    flash.c
  * @brief   ����KL46�ļƲ������-Flashģ��eepromԴ�ļ�
  * @author  ������
  * @version V1.0
  * @date    2015.4.28
  * @note    
  ******************************************************************************
  */

//����ͷ�ļ�
#include "flash.h" 

// Flash�������궨�� ���ڲ�ʹ�� 
#define CCIF    (1<<7)
#define ACCERR  (1<<5)
#define FPVIOL  (1<<4)
#define MGSTAT0 (1<<0)


//Flash����궨�壬�ڲ�ʹ��
#define RD1SEC    0x01   // ����������
#define PGMCHK    0x02   // д����
#define RDRSRC    0x03   // ��Ŀ������
#define PGM4      0x06   // д�볤��
#define ERSBLK    0x08   // ��������Flash
#define ERSSCR    0x09   // ����Flash����
#define RD1ALL    0x40   // �����еĿ�
#define RDONCE    0x41   // ֻ��һ��
#define PGMONCE   0x43   // ֻдһ��
#define ERSALL    0x44   // �������п�
#define VFYKEY    0x45   // ��֤���ŷ���Կ��

//=================�ڲ����ú�������==========================================
//==========================================================================
//�������ƣ�flash_cmd_launch
//�������أ�0-�ɹ� 1-ʧ��
//����˵������
//���ܸ�Ҫ������Flash����
//==========================================================================
static uint_32 flash_cmd_launch(void);
//===========================================================================

//=================�ⲿ�ӿں���==============================================
//==========================================================================
//�������ƣ�flash_init
//�������أ���
//����˵������
//���ܸ�Ҫ����ʼ��flashģ��
//==========================================================================
void flash_init(void)
{   
    // �ȴ��������
    while(!(FTFA_FSTAT & CCIF));
    
  // ������ʳ����־λ
    FTFA_FSTAT = ACCERR | FPVIOL;
    //������ģ����ƽ̨���ƼĴ�����PLACR_ESFC��Flashģ���д����
    //BSET(MCM_PLACR_ESFC_SHIFT,MCM_PLACR); 
    /*
    //������ģ����ƽ̨���ƼĴ�����PLACR_ESFC��Flashģ���д������
    BCLR(MCM_PLACR_ESFC_SHIFT,MCM_PLACR);   //��ʵ��۲������ã�
    */
}
//==========================================================================
//�������ƣ�flash_erase_sector
//�������أ�����ִ��ִ��״̬��0=��������0=�쳣��
//����˵����sectorNo�������ţ�KL25ʵ��ʹ��0~127��
//���ܸ�Ҫ������ָ��flash����
//==========================================================================
uint_8 flash_erase_sector(uint_16 sectorNo)
{
    union
    {
        uint_32  word;
        uint_8   byte[4];
    } dest;
    
    dest.word    = (uint_32)(sectorNo*(1<<10));

    // ���ò�������
    FTFA_FCCOB0 = ERSSCR; // ������������
    
    // ����Ŀ���ַ
    FTFA_FCCOB1 = dest.byte[2];
    FTFA_FCCOB2 = dest.byte[1];
    FTFA_FCCOB3 = dest.byte[0];
    
    // ִ����������
    if(1 == flash_cmd_launch())    //��ִ��������ִ���
        return 1;     //�����������
   
    // ������sector0ʱ��������豸
    if(dest.word <= 0x800)
    {
        // д��4�ֽ�
        FTFA_FCCOB0 = PGM4; 
        // ����Ŀ���ַ
        FTFA_FCCOB1 = 0x00;
        FTFA_FCCOB2 = 0x04;
        FTFA_FCCOB3 = 0x0C;
        // ����
        FTFA_FCCOB4 = 0xFF;
        FTFA_FCCOB5 = 0xFF;
        FTFA_FCCOB6 = 0xFF;
        FTFA_FCCOB7 = 0xFE;
        // ִ����������
        if(1 == flash_cmd_launch())  //��ִ��������ִ���
            return 2;   //�����������
    }  
    
    return 0;  //�ɹ�����
}
//==========================================================================
//�������ƣ�flash_write
//�������أ�����ִ��״̬��0=��������0=�쳣��
//����˵����sectNo��Ŀ�������� ��KL25ʵ��ʹ��0~127��
//         offset:д�������ڲ�ƫ�Ƶ�ַ��0~2043��
//         cnt��д���ֽ���Ŀ��0~2043��
//         buf��Դ���ݻ������׵�ַ
//���ܸ�Ҫ��flashд�����
//==========================================================================
uint_8 flash_write(uint_16 sectNo,uint_16 offset,uint_16 cnt,uint_8 buf[])
{
    uint_32 size;
    uint_32 destaddr;
    
    union
    {
        uint_32   word;
        uint_8  byte[4];
    } dest;
    
    if(offset%4 != 0)
        return 1;   //�����趨����ƫ����δ���루4�ֽڶ��룩
    
    // ����д������
    FTFA_FCCOB0 = PGM4;
    destaddr = (uint_32)(sectNo*(1<<10) + offset);//�����ַ
    dest.word = destaddr;
    for(size=0; size<cnt; size+=4, dest.word+=4, buf+=4)
    {
        // ����Ŀ���ַ
        FTFA_FCCOB1 = dest.byte[2];
        FTFA_FCCOB2 = dest.byte[1];
        FTFA_FCCOB3 = dest.byte[0];
 
        // ��������
        FTFA_FCCOB4 = buf[3];
        FTFA_FCCOB5 = buf[2];
        FTFA_FCCOB6 = buf[1];
        FTFA_FCCOB7 = buf[0];
        
        if(1 == flash_cmd_launch()) 
            return 2;  //д���������
    }
    
    return 0;  //�ɹ�ִ��
}
//==========================================================================
//�������ƣ�flash_secure
//�������أ�����ִ��״̬��0=��������0=�쳣��
//����˵������
//���ܸ�Ҫ��flash���ܲ���
//==========================================================================
uint_8 flash_secure(uint_8 key[])
{
    uint_8 vecdata[256];
    uint_16 i;
    uint_8* dataaddr;
    dataaddr=(uint_8*)0x400;
    for(i=0;i<8;i++)
 	    vecdata[i]=key[i];
     vecdata[8]=0xFF;         //�����ÿ鱣��
     vecdata[9]=0xFF;         //�����ÿ鱣��
     vecdata[10]=0xFF;        //�����ÿ鱣��
     vecdata[11]=0xFF;        //�����ÿ鱣��
     vecdata[12]=0x80;        //����оƬ���������������Կ����
     vecdata[13]=0xFF;        //Flashѡ��Ĵ���Ĭ������Ϊ0xff
     vecdata[14]=0xFF;        //�����ֶ�
     vecdata[15]=0xFF;        //�����ֶ�
     for(i=16;i<256;i++)
    	 vecdata[i]=dataaddr[i];//����ԭ��Flash�е�����
    union
    {
        uint_32   word;
        uint_8  byte[4];
    } dest;
        
    // ����д������
    FTFA_FCCOB0 = PGM4;
    dest.word = 0x400;
    dataaddr=vecdata;
    for(i=0; i<256; i+=4, dest.word+=4,dataaddr=dataaddr+4)
    {
	    // ����Ŀ���ַ
	    FTFA_FCCOB1 = dest.byte[2];
	    FTFA_FCCOB2 = dest.byte[1];
	    FTFA_FCCOB3 = dest.byte[0];

	    // ��������
	    FTFA_FCCOB4 = dataaddr[3];
	    FTFA_FCCOB5 = dataaddr[2];
	    FTFA_FCCOB6 = dataaddr[1];
	    FTFA_FCCOB7 = dataaddr[0];
        if(1 == flash_cmd_launch()) 
            return 2;  //д���������
    }
        return 0; 
}
//==========================================================================
//�������ƣ�flash_unsecure
//�������أ�����ִ��״̬��0=��������0=�쳣��
//����˵������
//���ܸ�Ҫ��ɾ����Կ������оƬ
//==========================================================================
uint_8 flash_unsecure()
{
    uint_8 vecdata[256];
    uint_16 i;
    uint_8* dataaddr;
    dataaddr=(uint_8*)0x400;
    for(i=0;i<8;i++)
        vecdata[i]=0xFF;
    vecdata[8]=0xFF;         //�����ÿ鱣��
    vecdata[9]=0xFF;         //�����ÿ鱣��
    vecdata[10]=0xFF;        //�����ÿ鱣��
    vecdata[11]=0xFF;        //�����ÿ鱣��
    vecdata[12]=0xFE;        //����оƬ
    vecdata[13]=0xFF;        //Flashѡ��Ĵ���Ĭ������Ϊ0xff
    vecdata[14]=0xFF;        //�����ֶ�
    vecdata[15]=0xFF;        //�����ֶ�
    for(i=16;i<256;i++)
        vecdata[i]=dataaddr[i];//����ԭ��Flash�е�����
    union
    {
        uint_32   word;
        uint_8  byte[4];
    }dest;
    // ����д������
    FTFA_FCCOB0 = PGM4;
    dest.word = 0x400;
    dataaddr=vecdata;
    for(i=0; i<256; i+=4, dest.word+=4,dataaddr=dataaddr+4)
    {
        // ����Ŀ���ַ
        FTFA_FCCOB1 = dest.byte[2];
        FTFA_FCCOB2 = dest.byte[1];
        FTFA_FCCOB3 = dest.byte[0];

        // ��������
        FTFA_FCCOB4 = dataaddr[3];
        FTFA_FCCOB5 = dataaddr[2];
        FTFA_FCCOB6 = dataaddr[1];
        FTFA_FCCOB7 = dataaddr[0];
        if(1 == flash_cmd_launch()) 
	        return 2;  //д���������
    }
    return 0; 
}

//==========================================================================
//�������ƣ�flash_protect
//�������أ�����ִ��״̬��0=��������0=�쳣��
//����˵������
//���ܸ�Ҫ��flash��������
//==========================================================================
void flash_protect()
{
	BCLR(2,FTFA_FPROT3);
}
//==========================================================================
//�������ƣ�flash_cmd_launch
//�������أ�0-�ɹ� 1-ʧ��
//����˵������
//���ܸ�Ҫ������Flash����
//==========================================================================
static uint_32 flash_cmd_launch(void)
{
    // ������ʴ����־λ�ͷǷ����ʱ�־λ
    FTFA_FSTAT = ACCERR | FPVIOL;
    
    // ��������
    FTFA_FSTAT = CCIF;

    // �ȴ��������
    while(!(FTFA_FSTAT & CCIF));

    // �������־
    if(FTFA_FSTAT & (ACCERR | FPVIOL | MGSTAT0))
        return 1 ; //ִ���������
    return 0; //ִ������ɹ�
}
//==========================================================================

