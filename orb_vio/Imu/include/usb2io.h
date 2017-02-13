//------------------------------------------------------------------------------//
//          �����������Ƽ����޹�˾                                              //
//         UI051 Ӧ�ñ�̽ӿ�(API)˵��                                          //
//                                                                              //
//    ��API������                                                               //
//    1. UI051 USB2IOоƬ                                                       //
//    2. Linux2.6.16����ϵͳ                                                    //
//                                                                              //
//    ��ϸ���½�����������Ƽ����޹�˾�ٷ���վhttp://freeeasy-life.com          //
//------------------------------------------------------------------------------//
#ifndef  _usb2io_H
#define  _usb2io_H

#include "libusb.h"
#define VID 0xC216
#define PID 0x0105
/***********�豸��������;���º����е�USB2IO_hdl��ָUSB2IO_Open���صľ��*******/
//�򿪶˿ڻ�ȡ���;  //Nbr�Ƕ˿ںţ���1��ʼ������Ϊ2/3/4...�����126
libusb_device_handle *USB2IO_Open(int Nbr);
//�رն˿ڣ��ڳ����˳�ǰ�ٹرն˿�; ���� 0: �ɹ���!0: ʧ��
int USB2IO_Close(libusb_device_handle *USB2IO_hdl);

/***********IO��������;���º����е�USB2IO_hdl��ָUSB2IO_Open���صľ��*******/
/** �������нӿں���                                                       **/
/**  IoNbr: IO��(1~10)                                                     **/
/**  ����ֵ 0: �ɹ���!0: ʧ��                                              **/
//����IO�����ʽ��IoCfg:0=����; IoCfg:2=OD+����, 3=PushPull�������;
int USB2IO_SetIoCfg(libusb_device_handle *USB2IO_hdl, int IoNbr, int IoCfg);
//����IO���ֵ��  IoOut:1=�����, 0=�����
int USB2IO_SetIoOut(libusb_device_handle *USB2IO_hdl, int IoNbr, int IoOut);
//��ȡIO�������, ��ȡֵ�����IoCfg��
int USB2IO_RdIoCfg(libusb_device_handle *USB2IO_hdl, int IoNbr, int *IoCfg);
//��ȡIO���ֵ(�����ȡ��������λ����USB2IO_SetIoOut������ֵ), ��ȡֵ�����IoOut��
int USB2IO_RdIoOut(libusb_device_handle *USB2IO_hdl, int IoNbr, int *IoOut);
//��ȡIO����ֵ(�����ȡ������ʵ�����ŵĵ�ƽֵ), ��ȡֵ�����PinValue��
//ע�⣺IO���ֵ������IO����Ĵ�����IO����ֵ��оƬ�����ϵ�ʵ�ʵ�ƽֵ��
//      ����һ�����������ȵģ��������IO�ܵ���ΧMCU����������Ӱ�죬�����п��ܲ���ȣ���ʱ��Ҫ��ϸ�鿴��Χ��·�Ƿ�������
int USB2IO_RdPin(libusb_device_handle *USB2IO_hdl, int IoNbr, int *PinValue);
//��ȡClkOut����� ClkOutCfg: 1=���Clk, 0=�ر�Clk
int USB2IO_SetClkOut(libusb_device_handle *USB2IO_hdl, int ClkOutCfg);
//��ȡClkOut���������, ��ȡֵ�����ClkOutCfg��
int USB2IO_RdClkOutCfg(libusb_device_handle *USB2IO_hdl, int *ClkOutCfg);

/***********SPI��������;���º����е�USB2IO_hdl��ָUSB2IO_Open���صľ��******/
/** �������нӿں���                                                       **/
/**  ����ֵ 0: �ɹ���!0: ʧ��                                              **/
/*********��׼��SPI MODE ��������********************************************/
/**    MODE0 CPOL=0 CPHA=0 SPI_CLK����ʱ�ǵ͵�ƽ; �����ز���               **/ 
/**    MODE1 CPOL=0 CPHA=1 SPI_CLK����ʱ�ǵ͵�ƽ; �½��ز���               **/
/**    MODE2 CPOL=1 CPHA=0 SPI_CLK����ʱ�Ǹߵ�ƽ; �½��ز���               **/
/**    MODE3 CPOL=1 CPHA=1 SPI_CLK����ʱ�Ǹߵ�ƽ; �����ز���               **/
/****************************************************************************/
//ʹ��SPI�ӿڣ�SPI�ӿڵ����IO���ý��Զ��ı�
int USB2IO_EnableSpi(libusb_device_handle *USB2IO_hdl);
//SPIд: DataLength:���ݳ���(1~136�ֽ�); DataBuf:����buf
int USB2IO_SpiWrite(libusb_device_handle *USB2IO_hdl, int DataLength, char *DataBuf);
//SPI��: DataLength:�����������ݳ���(1~136�ֽ�); ; DataBuf:����buf(��С����Ϊ256�ֽ�)
int USB2IO_SpiRead(libusb_device_handle *USB2IO_hdl, int DataLength, char *DataBuf);
//����SPI MODE: Mode0~3
int USB2IO_SetSpiMode(libusb_device_handle *USB2IO_hdl, int SpiMode);
//��ȡSPI MODE: Mode0~3
int USB2IO_GetSpiMode(libusb_device_handle *USB2IO_hdl, int *SpiMode);

/***********I2C��������;���º����е�USB2IO_hdl��ָUSB2IO_Open���صľ��******/
/** �������нӿں���                                                       **/
/**  ����ֵ 0: �ɹ���!0: ʧ��                                              **/
//ʹ��I2C�ӿڣ�I2C�ӿڵ����IO���ý��Զ��ı�
int USB2IO_EnableI2c(libusb_device_handle *USB2IO_hdl);
//I2Cд: 
//I2cAddr:I2C�豸��ַ; 
//CmdRegAddr: �����Ĵ�����ַ, ֻ�е�CmdRegAddrExistFlag!=0ʱ��Ч; 
//CmdRegAddrByteCnt: CmdRegAddr�ĳ���(0~4)(��λ:�ֽ�)  0: ������CmdRegAddr
//DataLength:���ݳ���(1~136�ֽ�); 
//DataBuf:����buf
int USB2IO_I2cWrite(libusb_device_handle *USB2IO_hdl, int I2cAddr, int CmdRegAddr, int CmdRegAddrByteCnt, int DataLength, char *DataBuf);
//I2C��: 
//I2cAddr:I2C�豸��ַ; 
//CmdRegAddr: �����Ĵ�����ַ, ֻ�е�CmdRegAddrByteCnt!=0ʱ��Ч; 
//CmdRegAddrByteCnt: CmdRegAddr�ĳ���(0~4)(��λ:�ֽ�)  0: ������CmdRegAddr
//DataLength:�����������ݳ���(1~136�ֽ�); 
//DataBuf:�������ݵ�����buf(��С����Ϊ256�ֽ�)
int USB2IO_I2cRead(libusb_device_handle *USB2IO_hdl, int I2cAddr, int CmdRegAddr, int CmdRegAddrByteCnt, int DataLength, char *DataBuf);
//����I2C�ٶ�: 0:80k 1:160k
int USB2IO_SetI2cSpeed(libusb_device_handle *USB2IO_hdl, int I2cSpeed);
//��ȡI2C�ٶ�: 0:80k 1:160k
int USB2IO_GetI2cSpeed(libusb_device_handle *USB2IO_hdl, int *I2cSpeed);

/***********UART��������;���º����е�USB2IO_hdl��ָUSB2IO_Open���صľ��******/
/**  �������нӿں���                                                       **/
/**  ����ֵ 0: �ɹ���!0: ʧ��                                               **/
//ʹ��UART�ӿڣ�UART�ӿڵ����IO���ý��Զ��ı�
int USB2IO_EnableUart(libusb_device_handle *USB2IO_hdl);
//UART���ͽ���
//����ֵ��0:�ɹ�; 1:���ճ�ʱ�����յ���ʵ�����ݳ���ΪActualReadDataLength; -1:ʧ��
//WrLen: �����͵����ݳ���(ȡֵ��Χ0~136;0��ʾ�����ݷ���)
//WrBuf: �����͵�����buf
//ExpRdLen: �������յ����ݳ���(ȡֵ��Χ0~136;0��ʾ�����������)
//ActRdLen: ʵ�ʽ��յ������ݳ���(ȡֵ��Χ0~136;0��ʾ�����������)
//RdBuf: �������ݵ�����buf(��С����Ϊ256�ֽ�)
//TimeOut:�������ݲ���Ҫ���ȴ����ݵ�ʱ��(��λ: s)��ȡֵ��Χ: 3~600s(Ҳ����10����)
int USB2IO_UartWrRd(libusb_device_handle *USB2IO_hdl, int WrLen, char *WrBuf, int ExpRdLen, int *ActRdLen, char *RdBuf, int TimeOut);
//���ò�����: UartBr=115200��9600
int USB2IO_SetUartBr(libusb_device_handle *USB2IO_hdl, int UartBr);
//��ȡ������ 115200��9600
int USB2IO_GetUartBr(libusb_device_handle *USB2IO_hdl, int *UartBr);

#endif