/*!
 * @file DFRobotDFPlayerMini.h
 * @brief DFPlayer - An Arduino Mini MP3 Player From DFRobot
 * @n Header file for DFRobot's DFPlayer
 *
 * @copyright	[DFRobot]( http://www.dfrobot.com ), 2016
 * @copyright	GNU Lesser General Public License
 *
 * @author [Angelo](Angelo.qiao@dfrobot.com)
 * @version  V1.0
 * @date  2016-12-07
 */

#include "Arduino.h"

#ifndef DFRobotDFPlayerMini_cpp
    #define DFRobotDFPlayerMini_cpp


#define DFPLAYER_EQ_NORMAL 0
#define DFPLAYER_EQ_POP 1
#define DFPLAYER_EQ_ROCK 2
#define DFPLAYER_EQ_JAZZ 3
#define DFPLAYER_EQ_CLASSIC 4
#define DFPLAYER_EQ_BASS 5

#define DFPLAYER_DEVICE_U_DISK 1
#define DFPLAYER_DEVICE_SD 2
#define DFPLAYER_DEVICE_AUX 3
#define DFPLAYER_DEVICE_SLEEP 4
#define DFPLAYER_DEVICE_FLASH 5

#define DFPLAYER_RECEIVED_LENGTH 10
#define DFPLAYER_SEND_LENGTH 10

//#define _DEBUG

enum HandleType{
  TimeOut,
  WrongStack,
  DFPlayerCardInserted,
  DFPlayerCardRemoved,
  DFPlayerCardOnline,
  DFPlayerPlayFinished,
  DFPlayerError
};

enum DFPlayerErrorType{
  Busy = 1,
  Sleeping,
  SerialWrongStack,
  CheckSumNotMatch,
  FileIndexOut,
  FileMismatch,
  Advertise
};


class DFRobotDFPlayerMini {
  Stream* _serial;
  
  unsigned long _timeOutTimer;
  unsigned long _timeOutDuration = 500;
  
  uint8_t _received[DFPLAYER_RECEIVED_LENGTH];
  uint8_t _sending[DFPLAYER_SEND_LENGTH] = {0x7E, 0xFF, 06, 00, 01, 00, 00, 00, 00, 0xEF};
  
  uint8_t _receivedIndex=0;

  void sendStack();
  void sendStack(uint8_t command);
  void sendStack(uint8_t command, uint16_t argument);
  void sendStack(uint8_t command, uint8_t argumentHigh, uint8_t argumentLow);

  void enableACK();
  void disableACK();
  
  void uint16ToArray(uint16_t value,uint8_t *array);
  
  uint16_t arrayToUint16(uint8_t *array);
  
  uint16_t calculateCheckSum(uint8_t *buffer);
  


  void parseStack();
  bool validateStack();
  
  uint8_t device = DFPLAYER_DEVICE_SD;
  
  
  enum Stack{
    Header = 0,
    Version = 1,
    Length = 2,
    Command = 3,
    ACK = 4,
    Parameter = 5,
    CheckSum = 7,
    End = 9
  };
  
  public:
  
  HandleType _handleType;
  uint8_t _handleCommand;
  uint16_t _handleParameter;
  bool _isAvailable = false;
  bool _isSending = false;
  
  bool handleMessage(HandleType type, uint16_t parameter = 0);
  bool handleError(HandleType type, uint16_t parameter = 0);

  uint8_t readCommand();
  
  bool begin(Stream& stream, bool isACK = true);
  
  bool waitAvailable();
  
  bool available();
  
  HandleType readType();
  
  uint16_t read();
  
  void setTimeOut(unsigned long timeOutDuration);
  
  void next();
  
  void previous();
  
  void play(int fileNumber=1);
  
  void volumeUp();
  
  void volumeDown();
  
  void volume(uint8_t volume);
  
  void EQ(uint8_t eq);
  
  void loop(int fileNumber);
  
  void outputDevice(uint8_t device);
  
  void sleep();
  
  void reset();
  
  void start();
  
  void pause();
  
  void playFolder(uint8_t folderNumber, uint8_t fileNumber);
  
  void outputSetting(bool enable, uint8_t gain);
  
  void enableLoopAll();
  
  void disableLoopAll();
  
  void playMp3Folder(int fileNumber);
  
  void advertise(int fileNumber);
  
  void playLargeFolder(uint8_t folderNumber, uint16_t fileNumber);
  
  void stopAdvertise();
  
  void stop();
  
  void loopFolder(int folderNumber);
  
  void randomAll();
  
  void enableLoop();
  
  void disableLoop();
  
  void enableDAC();
  
  void disableDAC();
  
  int readState();
  
  int readVolume();
  
  uint8_t readEQ();
  
  int readFileCounts(uint8_t device);
  
  int readCurrentFileNumber(uint8_t device);
  
  int readFileCountsInFolder(int folderNumber);
  
  int readFileCounts();
  
  int readCurrentFileNumber();
  
};

#endif
