# Discussion Document
[Project Discussion Document](https://docs.google.com/document/d/17FqQZBvIUeDZXvHoyFtpbia7zXl-SEKgaBjHs3DEvs0/edit?tab=t.0)

# Build & Run

## Using Docker (Recommended)
A `docker-compose` environment is provided to easily build and test both the `device` and `client` together. The source code is mounted directly into the containers, so you can edit the code locally and test immediately.

1. Ensure `docker` and `docker-compose` are installed.
2. Run the following command in the project root:
   ```bash
   docker-compose up
   ```
Docker will automatically build the CMake projects for both `device` and `client` in their respective `.build` directories, and then execute them. The client will start slightly after the device is ready. Both logs will be printed to the console. 

Press `Ctrl + C` to stop.

## device (WSL or linux)
```
cd device

# configuration
cmake -B .build .

# build
cmake --build .build

# run
.build/device
```

## Ubuntu 20.04 compatibility build notes

On Ubuntu 20.04 (GCC 9.4 / older libstdc++), you may hit compatibility issues when building this project.

- `<format>` may not be available in the default toolchain.
- `pthread_*` symbols may fail to link if thread libraries are not linked explicitly.
- Prebuilt static libraries may reference `std::__throw_bad_array_new_length()`, which is not exported on this toolchain.

This repository already includes compatibility fixes for Ubuntu 20.04 in the `device` target, so the normal commands below should work:

```
cd device
cmake -B .build .
cmake --build .build
```

## client (Windows)
1. Run the Visual Studio (This code was tested with Visual Studio 2026 Community)
2. Open the folder, "client" in VS
3. Build and run the application with ctrl + F5

# JSON configuration
client\client.cpp (line 11)

```
const char* msg_template =
R"(
{
  "frame": {
    "I": {
      "size": 262144,
      "num": 1,
      "interval": 10
    },
    "P": {
      "size": 12288,
      "num": 29,
      "interval": 10
    }
  },
  "num": %d
}
)";
```

Our environment shows distinct symptoms at interval values 1 and 10.

# LOG
## interval value 10
### device
```
(LOG) [main] NTIL ver.4.1.0.8-496-288
(LOG) [main] p2p initialization begins.
(LOG) [init] libntil version: 4.1.0.8-496-288
(LOG) [init] Start C2C process
[I][03-04 14:22:18.909][940204] {wincmpt} CQEvent: (0xab4c660)=>queue_size=(50)*(52)=2600
[I][03-04 14:22:18.910][940204] {c2c} memory allocation pass time = 1 ms
[I][03-04 14:22:18.910][940204] {c2c} Libntil version is 4.1.0.8-496-288, compiled at 16:00:38 Feb  4 2026
[I][03-04 14:22:18.910][940204] {c2c} MAX_LINE of Libntil is 12
[I][03-04 14:22:18.911][940204] {c2c} libntil initialization done, current version: 4.1.0.8-496-288
(LOG) [init] MAX_LINE=12
(LOG) [main] p2p daemon initialization success.
(LOG) [main] p2p chunk size=1280
(LOG) [CB-lpMessage][C2C_SERVICE_READY]
(LOG) [CB-lpMessage][C2C_REGISTER_DONE]
(LOG) [CB-lpMessage][C2C_INCOMING_DETECTED]
(LOG) [CB-lpMessage][C2C_INCOMING_STATE]
 ...event...from line 0
 ...A new incomming call! From 0PnCQ3ABI9CMheYe.NnZEfA_webgate@webgateinc.iptnet.net, to O7XU-4WOP@webgateinc.iptnet.net, custom-info is , auth-lv=0, line=0
(LOG) [CB-lpMessage][C2C_REMOTE_RSP]
(LOG) [CB-lpMessage][C2C_RTP_PRE_ALLOCATE]
(LOG) [CB-lpMessage][C2C_P2P_MODE]
 ...Media session has been established in P2P mode!
 ...socket=0, line=0
 ...NTIL_SendCommandByRtp to line 0 returns 48
 ...(arg2) peer=0PnCQ3ABI9CMheYe.NnZEfA_webgate@webgateinc.iptnet.net, custom-info=, auth-lv=0, line=0
(LOG) [CB-lpStartStreming] line=0
(LOG) [CB-lpCommand] line=0, arg1=0x81, tag=CONNECTED, msg=C2C_P2P_MODE-ok
(LOG)   [CB-lpCommand][CONNECTED] tag=CONNECTED msg=C2C_P2P_MODE-ok extra=0x0
(LOG) [CB-lpCommand] line=0, arg1=0x80, tag=test_spec.0001, msg=
{
  "frame": {
    "I": {
      "size": 262144,
      "num": 1,
      "interval": 10
    },
    "P": {
      "size": 12288,
      "num": 29,
      "interval": 10
    }
  },
  "num": 50
}

(LOG)   [CB-lpCommand][TEST] tag=test_spec.0001 msg=
{
  "frame": {
    "I": {
      "size": 262144,
      "num": 1,
      "interval": 10
    },
    "P": {
      "size": 12288,
      "num": 29,
      "interval": 10
    }
  },
  "num": 50
}
, extra=0x75ccac330c60 type=0x80
(LOG)   TID=1
(LOG)   TID=1, num=50
(LOG)   I-frame.size=262144, num=1, interval=10
(LOG)   P-frame.size=12288, num=29, interval=10
(LOG)   - (sendState) [1] : start
(LOG)   Sending... #0
(LOG) [CB-lpCommand] line=0, arg1=0x81, tag=test_state.0001, msg=start-ok
(LOG)   [CB-lpCommand][ACK] tag=test_state.0001 msg=start-ok, extra=0x0
(LOG)   Sending... #1
(LOG)   Sending... #2
(LOG) [CB-lpMessage][C2C_QOS_LEVEL_DOWN]
(LOG)   Sending... #3
(LOG)   Sending... #4
(LOG)   Sending... #5
(LOG)   Sending... #6
(LOG)   Sending... #7
(LOG)   Sending... #8
(LOG)   Sending... #9
(LOG)   Sending... #10
(LOG)   Sending... #11
(LOG)   Sending... #12
(LOG)   Sending... #13
(LOG)   Sending... #14
(LOG)   Sending... #15
(LOG)   Sending... #16
(LOG)   Sending... #17
(LOG)   Sending... #18
(LOG)   Sending... #19
(LOG)   Sending... #20
(LOG)   Sending... #21
(LOG)   Sending... #22
(LOG)   Sending... #23
(LOG)   Sending... #24
(LOG)   Sending... #25
(LOG)   Sending... #26
(LOG)   Sending... #27
(LOG)   Sending... #28
(LOG)   Sending... #29
(LOG)   Sending... #30
(LOG)   Sending... #31
(LOG)   Sending... #32
(LOG)   Sending... #33
(LOG)   Sending... #34
(LOG)   Sending... #35
(LOG)   Sending... #36
(LOG)   Sending... #37
(LOG)   Sending... #38
(LOG) [CB-lpMessage][C2C_QOS_LEVEL_DOWN]
(LOG)   Sending... #39
(LOG)   Sending... #40
(LOG)   Sending... #41
(LOG)   Sending... #42
(LOG)   Sending... #43
(LOG)   Sending... #44
(LOG)   Sending... #45
(LOG)   Sending... #46
(LOG)   Sending... #47
(LOG)   Sending... #48
(LOG)   Sending... #49
(LOG)   - (sendState) [1] : done
(LOG)   Sending... DONE
(LOG)   Waiting 1secs to terminate this connection
(LOG) [CB-lpCommand] line=0, arg1=0x81, tag=test_state.0001, msg=done-ok
(LOG)   [CB-lpCommand][ACK] tag=test_state.0001 msg=done-ok, extra=0x0
(LOG) [CB-lpCloseStreaming] line=0
(LOG) [CB-lpMessage][C2C_CALL_TERMINATED]
 ...Media session has been stopped ... peer=0PnCQ3ABI9CMheYe.NnZEfA_webgate@webgateinc.iptnet.net, line=0
(LOG)  (jobSendingVideo) done
```

### client
```
NTIL_StartConnection(O7XU-4WOP@webgateinc.iptnet.net, 0PnCQ3ABI9CMheYe.NnZEfA_webgate@webgateinc.iptnet.net, B2E2IE43QSUWY6C9g4k26Csuw4A34645) = 0
C2C_Message[48]<1772601744,917831141536> lineID:0
[C2C_SERVICE_READY]
C2C_Message[3]<3,917831142272> lineID:0
[C2C_REGISTER_DONE]
C2C_Message[5]<6,0> lineID:0
[C2C_OUTGOING_STATE]
C2C_Message[5]<7,2470069705152> lineID:0
C2C_Message[9]<0,0> lineID:0
C2C_Message[74]<0,0> lineID:0
[C2C_OUTGOING_STATE]
[C2C_REMOTE_RSP]
[CB-lpStartStreming] line=0000000000000000
C2C_Message[10]<0,2470069705152> lineID:0
[C2C_RTP_PRE_ALLOCATE]
C2C_CommandCallback[800919218](0] CONNECTED:C2C_P2P_MODE (0x80)
[C2C_P2P_MODE]
C2C_CommandCallback[800919250](0] test_spec.0001:ACK_test_spec.0001 (0x81)
C2C_CommandCallback[800919250](0] test_state.0001:start (0x80)
START : TID=1 (800919250)
VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVC2C_CommandCallback[800934531](0] test_state.0001:done (0x80)
STOP : TID=1 (800934531)
[CB-lpCloseStreaming] line=0
C2C_Message[16]<2470069678176,2470069656204> lineID:0
[C2C_CALL_TERMINATED]

============================================
         CHECK
============================================
============================================
         RESULT
============================================
 - CMD time diff=15.28s (800919250 ~ 800934531)
 - expect : frames=1500
 - received : frames=1500, fps=98.16
 - loss frames=0, ratio=  0.0%
 - DONE
[C2C_NOANSWER]
NTIL_TerminateConnection(0)
```

## interval value 1
### device
```
(LOG) [main] NTIL ver.4.1.0.8-496-288
(LOG) [main] p2p initialization begins.
(LOG) [init] libntil version: 4.1.0.8-496-288
(LOG) [init] Start C2C process
[I][03-04 14:24:59.122][941750] {wincmpt} CQEvent: (0x10e37660)=>queue_size=(50)*(52)=2600
[I][03-04 14:24:59.123][941750] {c2c} memory allocation pass time = 1 ms
[I][03-04 14:24:59.123][941750] {c2c} Libntil version is 4.1.0.8-496-288, compiled at 16:00:38 Feb  4 2026
[I][03-04 14:24:59.123][941750] {c2c} MAX_LINE of Libntil is 12
[I][03-04 14:24:59.123][941750] {c2c} libntil initialization done, current version: 4.1.0.8-496-288
(LOG) [init] MAX_LINE=12
(LOG) [main] p2p daemon initialization success.
(LOG) [main] p2p chunk size=1280
(LOG) [CB-lpMessage][C2C_SERVICE_READY]
(LOG) [CB-lpMessage][C2C_REGISTER_DONE]
(LOG) [CB-lpMessage][C2C_INCOMING_DETECTED]
(LOG) [CB-lpMessage][C2C_INCOMING_STATE]
 ...event...from line 0
 ...A new incomming call! From 0PnCQ3ABI9CMheYe.NnZEfA_webgate@webgateinc.iptnet.net, to O7XU-4WOP@webgateinc.iptnet.net, custom-info is , auth-lv=0, line=0
(LOG) [CB-lpMessage][C2C_REMOTE_RSP]
(LOG) [CB-lpMessage][C2C_RTP_PRE_ALLOCATE]
(LOG) [CB-lpMessage][C2C_P2P_MODE]
 ...Media session has been established in P2P mode!
 ...socket=0, line=0
 ...NTIL_SendCommandByRtp to line 0 returns 48
 ...(arg2) peer=0PnCQ3ABI9CMheYe.NnZEfA_webgate@webgateinc.iptnet.net, custom-info=, auth-lv=0, line=0
(LOG) [CB-lpStartStreming] line=0
(LOG) [CB-lpCommand] line=0, arg1=0x81, tag=CONNECTED, msg=C2C_P2P_MODE-ok
(LOG)   [CB-lpCommand][CONNECTED] tag=CONNECTED msg=C2C_P2P_MODE-ok extra=0x0
(LOG) [CB-lpCommand] line=0, arg1=0x80, tag=test_spec.0001, msg=
{
  "frame": {
    "I": {
      "size": 262144,
      "num": 1,
      "interval": 1
    },
    "P": {
      "size": 12288,
      "num": 29,
      "interval": 1
    }
  },
  "num": 50
}

(LOG)   [CB-lpCommand][TEST] tag=test_spec.0001 msg=
{
  "frame": {
    "I": {
      "size": 262144,
      "num": 1,
      "interval": 1
    },
    "P": {
      "size": 12288,
      "num": 29,
      "interval": 1
    }
  },
  "num": 50
}
, extra=0x7b2c80330c60 type=0x80
(LOG)   TID=1
(LOG)   TID=1, num=50
(LOG)   I-frame.size=262144, num=1, interval=1
(LOG)   P-frame.size=12288, num=29, interval=1
(LOG)   - (sendState) [1] : start
(LOG)   Sending... #0
(LOG) [CB-lpCommand] line=0, arg1=0x81, tag=test_state.0001, msg=start-ok
(LOG)   [CB-lpCommand][ACK] tag=test_state.0001 msg=start-ok, extra=0x0
(LOG)   Sending... #1
(LOG)   Sending... #2
(LOG)   Sending... #3
(LOG)   Sending... #4
(LOG)   Sending... #5
(LOG)   Sending... #6
(LOG)   Sending... #7
(LOG)   Sending... #8
(LOG)   Sending... #9
(LOG)   Sending... #10
(LOG)   Sending... #11
(LOG)   Sending... #12
(LOG)   Sending... #13
(LOG)   Sending... #14
(LOG)   Sending... #15
(LOG)   Sending... #16
(LOG)   Sending... #17
(LOG)   Sending... #18
(LOG)   Sending... #19
(LOG)   Sending... #20
(LOG)   Sending... #21
(LOG)   Sending... #22
(LOG)   Sending... #23
(LOG)   Sending... #24
(LOG)   Sending... #25
(LOG) [CB-lpMessage][C2C_QOS_LEVEL_DOWN]
(LOG)   Sending... #26
(LOG)   Sending... #27
(LOG)   Sending... #28
(LOG)   Sending... #29
(LOG)   Sending... #30
(LOG)   Sending... #31
(LOG)   Sending... #32
(LOG)   Sending... #33
(LOG)   Sending... #34
(LOG)   Sending... #35
(LOG)   Sending... #36
(LOG)   Sending... #37
(LOG)   Sending... #38
(LOG)   Sending... #39
(LOG)   Sending... #40
(LOG)   Sending... #41
(LOG)   Sending... #42
(LOG)   Sending... #43
(LOG)   Sending... #44
(LOG)   Sending... #45
(LOG)   Sending... #46
(LOG)   Sending... #47
(LOG)   Sending... #48
(LOG)   Sending... #49
(LOG)   - (sendState) [1] : done
(LOG)   Sending... DONE
(LOG)   Waiting 1secs to terminate this connection
(LOG) [CB-lpCommand] line=0, arg1=0x81, tag=test_state.0001, msg=done-ok
(LOG)   [CB-lpCommand][ACK] tag=test_state.0001 msg=done-ok, extra=0x0
(LOG) [CB-lpCloseStreaming] line=0
(LOG) [CB-lpMessage][C2C_CALL_TERMINATED]
 ...Media session has been stopped ... peer=0PnCQ3ABI9CMheYe.NnZEfA_webgate@webgateinc.iptnet.net, line=0
(LOG)  (jobSendingVideo) done
```

### client
```
NTIL_StartConnection(O7XU-4WOP@webgateinc.iptnet.net, 0PnCQ3ABI9CMheYe.NnZEfA_webgate@webgateinc.iptnet.net, B2E2IE43QSUWY6C9g4k26Csuw4A34645) = 0
C2C_Message[48]<1772601905,252184609904> lineID:0
[C2C_SERVICE_READY]
C2C_Message[3]<3,252184610640> lineID:0
[C2C_REGISTER_DONE]
C2C_Message[5]<6,0> lineID:0
[C2C_OUTGOING_STATE]
C2C_Message[5]<7,2133102003184> lineID:0
C2C_Message[9]<0,0> lineID:0
C2C_Message[74]<0,0> lineID:0
[C2C_OUTGOING_STATE]
[C2C_REMOTE_RSP]
[CB-lpStartStreming] line=0000000000000000
C2C_Message[10]<0,2133102003184> lineID:0
[C2C_RTP_PRE_ALLOCATE]
C2C_CommandCallback[801080640](0] CONNECTED:C2C_P2P_MODE (0x80)
[C2C_P2P_MODE]
C2C_CommandCallback[801080671](0] test_spec.0001:ACK_test_spec.0001 (0x81)
C2C_CommandCallback[801080671](0] test_state.0001:start (0x80)
START : TID=1 (801080671)
VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVC2C_CommandCallback[801082421](0] test_state.0001:done (0x80)
STOP : TID=1 (801082421)
VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV[CB-lpCloseStreaming] line=0
C2C_Message[16]<2133101983104,2133101948007> lineID:0
[C2C_CALL_TERMINATED]

============================================
         CHECK
============================================
 - GOP #0 testing :  Sequence error : 3 expected, but not 22
     - [801080718] OK : tid=1, gop=0, frame=0, crc32=0x83ac1b14
     - [801080718] OK : tid=1, gop=0, frame=1, crc32=0xe5756332
     - [801080718] OK : tid=1, gop=0, frame=2, crc32=0x9511f04a
     - [801080765] OK : tid=1, gop=0, frame=22, crc32=0xe47f956f
     - [801080765] OK : tid=1, gop=0, frame=23, crc32=0x74d220e7
     - [801080765] OK : tid=1, gop=0, frame=24, crc32=0x4b6b39f
     - [801080765] OK : tid=1, gop=0, frame=25, crc32=0xbb3edaf4
     - [801080765] OK : tid=1, gop=0, frame=26, crc32=0xcb5a498c
     - [801080765] OK : tid=1, gop=0, frame=27, crc32=0x5bf7fc04
     - [801080765] OK : tid=1, gop=0, frame=28, crc32=0x2b936f7c
     - [801080765] OK : tid=1, gop=0, frame=29, crc32=0xa1dd9155
  - (error) no GOP #1
 - GOP #2 testing :  Sequence error : 1 expected, but not 22
     - [801080765] OK : tid=1, gop=2, frame=0, crc32=0x18294483
     - [801080843] OK : tid=1, gop=2, frame=22, crc32=0xe47f956f
     - [801080843] OK : tid=1, gop=2, frame=23, crc32=0x74d220e7
     - [801080843] OK : tid=1, gop=2, frame=24, crc32=0x4b6b39f
     - [801080843] OK : tid=1, gop=2, frame=25, crc32=0xbb3edaf4
     - [801080843] OK : tid=1, gop=2, frame=26, crc32=0xcb5a498c
     - [801080843] OK : tid=1, gop=2, frame=27, crc32=0x5bf7fc04
     - [801080843] OK : tid=1, gop=2, frame=28, crc32=0x2b936f7c
     - [801080843] OK : tid=1, gop=2, frame=29, crc32=0xa1dd9155
 - GOP #3 testing :  Sequence error : 1 expected, but not 22
     - [801080843] OK : tid=1, gop=3, frame=0, crc32=0xb8536868
     - [801080859] OK : tid=1, gop=3, frame=22, crc32=0xe47f956f
     - [801080859] OK : tid=1, gop=3, frame=23, crc32=0x74d220e7
     - [801080859] OK : tid=1, gop=3, frame=24, crc32=0x4b6b39f
     - [801080859] OK : tid=1, gop=3, frame=25, crc32=0xbb3edaf4
     - [801080859] OK : tid=1, gop=3, frame=26, crc32=0xcb5a498c
     - [801080859] OK : tid=1, gop=3, frame=27, crc32=0x5bf7fc04
     - [801080859] OK : tid=1, gop=3, frame=28, crc32=0x2b936f7c
     - [801080859] OK : tid=1, gop=3, frame=29, crc32=0xa1dd9155
  - (error) no GOP #4
 - GOP #5 testing :  Sequence error : 0 expected, but not 22
     - [801080937] OK : tid=1, gop=5, frame=22, crc32=0xe47f956f
     - [801080937] OK : tid=1, gop=5, frame=23, crc32=0x74d220e7
     - [801080937] OK : tid=1, gop=5, frame=24, crc32=0x4b6b39f
     - [801080937] OK : tid=1, gop=5, frame=25, crc32=0xbb3edaf4
     - [801080937] OK : tid=1, gop=5, frame=26, crc32=0xcb5a498c
     - [801080937] OK : tid=1, gop=5, frame=27, crc32=0x5bf7fc04
     - [801080937] OK : tid=1, gop=5, frame=28, crc32=0x2b936f7c
     - [801080937] OK : tid=1, gop=5, frame=29, crc32=0xa1dd9155
  - (error) no GOP #6
 - GOP #7 testing :  Sequence error : 1 expected, but not 23
     - [801080937] OK : tid=1, gop=7, frame=0, crc32=0x5428d107
     - [801081015] OK : tid=1, gop=7, frame=23, crc32=0x74d220e7
     - [801081015] OK : tid=1, gop=7, frame=24, crc32=0x4b6b39f
     - [801081015] OK : tid=1, gop=7, frame=25, crc32=0xbb3edaf4
     - [801081015] OK : tid=1, gop=7, frame=26, crc32=0xcb5a498c
     - [801081015] OK : tid=1, gop=7, frame=27, crc32=0x5bf7fc04
     - [801081015] OK : tid=1, gop=7, frame=28, crc32=0x2b936f7c
     - [801081015] OK : tid=1, gop=7, frame=29, crc32=0xa1dd9155
  - (error) no GOP #8
 - GOP #9 testing :  Sequence error : 0 expected, but not 23
     - [801081093] OK : tid=1, gop=9, frame=23, crc32=0x74d220e7
     - [801081093] OK : tid=1, gop=9, frame=24, crc32=0x4b6b39f
     - [801081093] OK : tid=1, gop=9, frame=25, crc32=0xbb3edaf4
     - [801081093] OK : tid=1, gop=9, frame=26, crc32=0xcb5a498c
     - [801081093] OK : tid=1, gop=9, frame=27, crc32=0x5bf7fc04
     - [801081093] OK : tid=1, gop=9, frame=28, crc32=0x2b936f7c
     - [801081093] OK : tid=1, gop=9, frame=29, crc32=0xa1dd9155
  - (error) no GOP #10
 - GOP #11 testing :  Sequence error : 0 expected, but not 1
     - [801081140] OK : tid=1, gop=11, frame=1, crc32=0xe5756332
     - [801081140] OK : tid=1, gop=11, frame=2, crc32=0x9511f04a
     - [801081140] OK : tid=1, gop=11, frame=3, crc32=0x5bc45c2
     - [801081140] OK : tid=1, gop=11, frame=4, crc32=0x75d8d6ba
     - [801081140] OK : tid=1, gop=11, frame=5, crc32=0xff962893
     - [801081140] OK : tid=1, gop=11, frame=6, crc32=0x8ff2bbeb
     - [801081140] OK : tid=1, gop=11, frame=7, crc32=0x1f5f0e63
     - [801081140] OK : tid=1, gop=11, frame=8, crc32=0x6f3b9d1b
     - [801081140] OK : tid=1, gop=11, frame=9, crc32=0xd0b3f470
     - [801081140] OK : tid=1, gop=11, frame=10, crc32=0xa0d76708
     - [801081140] OK : tid=1, gop=11, frame=11, crc32=0x307ad280
     - [801081140] OK : tid=1, gop=11, frame=12, crc32=0x401e41f8
     - [801081140] OK : tid=1, gop=11, frame=13, crc32=0xca50bfd1
     - [801081140] OK : tid=1, gop=11, frame=14, crc32=0xba342ca9
     - [801081140] OK : tid=1, gop=11, frame=15, crc32=0x2a999921
     - [801081140] OK : tid=1, gop=11, frame=16, crc32=0x5afd0a59
     - [801081140] OK : tid=1, gop=11, frame=17, crc32=0x8ef84db6
     - [801081140] OK : tid=1, gop=11, frame=18, crc32=0xfe9cdece
     - [801081140] OK : tid=1, gop=11, frame=19, crc32=0x6e316b46
     - [801081140] OK : tid=1, gop=11, frame=20, crc32=0x1e55f83e
     - [801081140] OK : tid=1, gop=11, frame=21, crc32=0x941b0617
     - [801081140] OK : tid=1, gop=11, frame=22, crc32=0xe47f956f
     - [801081140] OK : tid=1, gop=11, frame=23, crc32=0x74d220e7
     - [801081140] OK : tid=1, gop=11, frame=24, crc32=0x4b6b39f
     - [801081140] OK : tid=1, gop=11, frame=25, crc32=0xbb3edaf4
     - [801081140] OK : tid=1, gop=11, frame=26, crc32=0xcb5a498c
     - [801081140] OK : tid=1, gop=11, frame=27, crc32=0x5bf7fc04
     - [801081140] OK : tid=1, gop=11, frame=28, crc32=0x2b936f7c
     - [801081140] OK : tid=1, gop=11, frame=29, crc32=0xa1dd9155
 - GOP #12 testing :  Sequence error : 0 expected, but not 1
     - [801081187] OK : tid=1, gop=12, frame=1, crc32=0xe5756332
     - [801081187] OK : tid=1, gop=12, frame=2, crc32=0x9511f04a
     - [801081187] OK : tid=1, gop=12, frame=3, crc32=0x5bc45c2
     - [801081187] OK : tid=1, gop=12, frame=4, crc32=0x75d8d6ba
     - [801081187] OK : tid=1, gop=12, frame=5, crc32=0xff962893
     - [801081187] OK : tid=1, gop=12, frame=6, crc32=0x8ff2bbeb
     - [801081187] OK : tid=1, gop=12, frame=7, crc32=0x1f5f0e63
     - [801081187] OK : tid=1, gop=12, frame=8, crc32=0x6f3b9d1b
     - [801081187] OK : tid=1, gop=12, frame=9, crc32=0xd0b3f470
     - [801081187] OK : tid=1, gop=12, frame=10, crc32=0xa0d76708
     - [801081187] OK : tid=1, gop=12, frame=11, crc32=0x307ad280
     - [801081187] OK : tid=1, gop=12, frame=12, crc32=0x401e41f8
     - [801081187] OK : tid=1, gop=12, frame=13, crc32=0xca50bfd1
     - [801081187] OK : tid=1, gop=12, frame=14, crc32=0xba342ca9
     - [801081187] OK : tid=1, gop=12, frame=15, crc32=0x2a999921
     - [801081187] OK : tid=1, gop=12, frame=16, crc32=0x5afd0a59
     - [801081187] OK : tid=1, gop=12, frame=17, crc32=0x8ef84db6
     - [801081187] OK : tid=1, gop=12, frame=18, crc32=0xfe9cdece
     - [801081187] OK : tid=1, gop=12, frame=19, crc32=0x6e316b46
     - [801081187] OK : tid=1, gop=12, frame=20, crc32=0x1e55f83e
     - [801081187] OK : tid=1, gop=12, frame=21, crc32=0x941b0617
     - [801081187] OK : tid=1, gop=12, frame=22, crc32=0xe47f956f
     - [801081187] OK : tid=1, gop=12, frame=23, crc32=0x74d220e7
     - [801081187] OK : tid=1, gop=12, frame=24, crc32=0x4b6b39f
     - [801081187] OK : tid=1, gop=12, frame=25, crc32=0xbb3edaf4
     - [801081187] OK : tid=1, gop=12, frame=26, crc32=0xcb5a498c
     - [801081187] OK : tid=1, gop=12, frame=27, crc32=0x5bf7fc04
     - [801081187] OK : tid=1, gop=12, frame=28, crc32=0x2b936f7c
     - [801081187] OK : tid=1, gop=12, frame=29, crc32=0xa1dd9155
 - GOP #13 testing :  Sequence error : 1 expected, but not 23
     - [801081187] OK : tid=1, gop=13, frame=0, crc32=0xcc2bfa0f
     - [801081234] OK : tid=1, gop=13, frame=23, crc32=0x74d220e7
     - [801081234] OK : tid=1, gop=13, frame=24, crc32=0x4b6b39f
     - [801081234] OK : tid=1, gop=13, frame=25, crc32=0xbb3edaf4
     - [801081234] OK : tid=1, gop=13, frame=26, crc32=0xcb5a498c
     - [801081234] OK : tid=1, gop=13, frame=27, crc32=0x5bf7fc04
     - [801081234] OK : tid=1, gop=13, frame=28, crc32=0x2b936f7c
     - [801081234] OK : tid=1, gop=13, frame=29, crc32=0xa1dd9155
  - (error) no GOP #14
 - GOP #15 testing :  Sequence error : 0 expected, but not 1
     - [801081281] OK : tid=1, gop=15, frame=1, crc32=0xe5756332
     - [801081281] OK : tid=1, gop=15, frame=2, crc32=0x9511f04a
     - [801081281] OK : tid=1, gop=15, frame=3, crc32=0x5bc45c2
     - [801081281] OK : tid=1, gop=15, frame=4, crc32=0x75d8d6ba
     - [801081281] OK : tid=1, gop=15, frame=5, crc32=0xff962893
     - [801081281] OK : tid=1, gop=15, frame=6, crc32=0x8ff2bbeb
     - [801081281] OK : tid=1, gop=15, frame=7, crc32=0x1f5f0e63
     - [801081281] OK : tid=1, gop=15, frame=8, crc32=0x6f3b9d1b
     - [801081281] OK : tid=1, gop=15, frame=9, crc32=0xd0b3f470
     - [801081281] OK : tid=1, gop=15, frame=10, crc32=0xa0d76708
     - [801081281] OK : tid=1, gop=15, frame=11, crc32=0x307ad280
     - [801081281] OK : tid=1, gop=15, frame=12, crc32=0x401e41f8
     - [801081281] OK : tid=1, gop=15, frame=13, crc32=0xca50bfd1
     - [801081281] OK : tid=1, gop=15, frame=14, crc32=0xba342ca9
     - [801081281] OK : tid=1, gop=15, frame=15, crc32=0x2a999921
     - [801081281] OK : tid=1, gop=15, frame=16, crc32=0x5afd0a59
     - [801081281] OK : tid=1, gop=15, frame=17, crc32=0x8ef84db6
     - [801081281] OK : tid=1, gop=15, frame=18, crc32=0xfe9cdece
     - [801081281] OK : tid=1, gop=15, frame=19, crc32=0x6e316b46
     - [801081281] OK : tid=1, gop=15, frame=20, crc32=0x1e55f83e
     - [801081281] OK : tid=1, gop=15, frame=21, crc32=0x941b0617
     - [801081281] OK : tid=1, gop=15, frame=22, crc32=0xe47f956f
     - [801081281] OK : tid=1, gop=15, frame=23, crc32=0x74d220e7
     - [801081281] OK : tid=1, gop=15, frame=24, crc32=0x4b6b39f
     - [801081281] OK : tid=1, gop=15, frame=25, crc32=0xbb3edaf4
     - [801081281] OK : tid=1, gop=15, frame=26, crc32=0xcb5a498c
     - [801081281] OK : tid=1, gop=15, frame=27, crc32=0x5bf7fc04
     - [801081281] OK : tid=1, gop=15, frame=28, crc32=0x2b936f7c
     - [801081281] OK : tid=1, gop=15, frame=29, crc32=0xa1dd9155
 - GOP #17 testing :  Sequence error : 0 expected, but not 1
     - [801081359] OK : tid=1, gop=17, frame=1, crc32=0xe5756332
     - [801081359] OK : tid=1, gop=17, frame=2, crc32=0x9511f04a
     - [801081359] OK : tid=1, gop=17, frame=3, crc32=0x5bc45c2
     - [801081359] OK : tid=1, gop=17, frame=4, crc32=0x75d8d6ba
     - [801081359] OK : tid=1, gop=17, frame=5, crc32=0xff962893
     - [801081359] OK : tid=1, gop=17, frame=6, crc32=0x8ff2bbeb
     - [801081359] OK : tid=1, gop=17, frame=7, crc32=0x1f5f0e63
     - [801081359] OK : tid=1, gop=17, frame=8, crc32=0x6f3b9d1b
     - [801081359] OK : tid=1, gop=17, frame=9, crc32=0xd0b3f470
     - [801081359] OK : tid=1, gop=17, frame=10, crc32=0xa0d76708
     - [801081359] OK : tid=1, gop=17, frame=11, crc32=0x307ad280
     - [801081359] OK : tid=1, gop=17, frame=12, crc32=0x401e41f8
     - [801081359] OK : tid=1, gop=17, frame=13, crc32=0xca50bfd1
     - [801081359] OK : tid=1, gop=17, frame=14, crc32=0xba342ca9
     - [801081359] OK : tid=1, gop=17, frame=15, crc32=0x2a999921
     - [801081359] OK : tid=1, gop=17, frame=16, crc32=0x5afd0a59
     - [801081359] OK : tid=1, gop=17, frame=17, crc32=0x8ef84db6
     - [801081359] OK : tid=1, gop=17, frame=18, crc32=0xfe9cdece
     - [801081359] OK : tid=1, gop=17, frame=19, crc32=0x6e316b46
     - [801081359] OK : tid=1, gop=17, frame=20, crc32=0x1e55f83e
     - [801081359] OK : tid=1, gop=17, frame=21, crc32=0x941b0617
     - [801081359] OK : tid=1, gop=17, frame=22, crc32=0xe47f956f
     - [801081359] OK : tid=1, gop=17, frame=23, crc32=0x74d220e7
     - [801081359] OK : tid=1, gop=17, frame=24, crc32=0x4b6b39f
     - [801081359] OK : tid=1, gop=17, frame=25, crc32=0xbb3edaf4
     - [801081359] OK : tid=1, gop=17, frame=26, crc32=0xcb5a498c
     - [801081359] OK : tid=1, gop=17, frame=27, crc32=0x5bf7fc04
     - [801081359] OK : tid=1, gop=17, frame=28, crc32=0x2b936f7c
     - [801081359] OK : tid=1, gop=17, frame=29, crc32=0xa1dd9155
 - GOP #18 testing :  Sequence error : 0 expected, but not 1
     - [801081375] OK : tid=1, gop=18, frame=1, crc32=0xe5756332
 - GOP #19 testing :  Sequence error : 0 expected, but not 1
     - [801081421] OK : tid=1, gop=19, frame=1, crc32=0xe5756332
     - [801081421] OK : tid=1, gop=19, frame=2, crc32=0x9511f04a
     - [801081421] OK : tid=1, gop=19, frame=3, crc32=0x5bc45c2
     - [801081421] OK : tid=1, gop=19, frame=4, crc32=0x75d8d6ba
     - [801081421] OK : tid=1, gop=19, frame=5, crc32=0xff962893
     - [801081421] OK : tid=1, gop=19, frame=6, crc32=0x8ff2bbeb
     - [801081421] OK : tid=1, gop=19, frame=7, crc32=0x1f5f0e63
     - [801081421] OK : tid=1, gop=19, frame=8, crc32=0x6f3b9d1b
     - [801081421] OK : tid=1, gop=19, frame=9, crc32=0xd0b3f470
     - [801081421] OK : tid=1, gop=19, frame=10, crc32=0xa0d76708
     - [801081421] OK : tid=1, gop=19, frame=11, crc32=0x307ad280
     - [801081421] OK : tid=1, gop=19, frame=12, crc32=0x401e41f8
     - [801081421] OK : tid=1, gop=19, frame=13, crc32=0xca50bfd1
     - [801081421] OK : tid=1, gop=19, frame=14, crc32=0xba342ca9
     - [801081421] OK : tid=1, gop=19, frame=15, crc32=0x2a999921
     - [801081421] OK : tid=1, gop=19, frame=16, crc32=0x5afd0a59
     - [801081421] OK : tid=1, gop=19, frame=17, crc32=0x8ef84db6
     - [801081421] OK : tid=1, gop=19, frame=18, crc32=0xfe9cdece
     - [801081421] OK : tid=1, gop=19, frame=19, crc32=0x6e316b46
     - [801081421] OK : tid=1, gop=19, frame=20, crc32=0x1e55f83e
     - [801081421] OK : tid=1, gop=19, frame=21, crc32=0x941b0617
     - [801081421] OK : tid=1, gop=19, frame=22, crc32=0xe47f956f
     - [801081421] OK : tid=1, gop=19, frame=23, crc32=0x74d220e7
     - [801081421] OK : tid=1, gop=19, frame=24, crc32=0x4b6b39f
     - [801081421] OK : tid=1, gop=19, frame=25, crc32=0xbb3edaf4
     - [801081421] OK : tid=1, gop=19, frame=26, crc32=0xcb5a498c
     - [801081421] OK : tid=1, gop=19, frame=27, crc32=0x5bf7fc04
     - [801081421] OK : tid=1, gop=19, frame=28, crc32=0x2b936f7c
     - [801081421] OK : tid=1, gop=19, frame=29, crc32=0xa1dd9155
 - GOP #22 testing :  Sequence error : 0 expected, but not 22
     - [801081531] OK : tid=1, gop=22, frame=22, crc32=0xe47f956f
     - [801081531] OK : tid=1, gop=22, frame=23, crc32=0x74d220e7
     - [801081531] OK : tid=1, gop=22, frame=24, crc32=0x4b6b39f
     - [801081531] OK : tid=1, gop=22, frame=25, crc32=0xbb3edaf4
     - [801081531] OK : tid=1, gop=22, frame=26, crc32=0xcb5a498c
     - [801081531] OK : tid=1, gop=22, frame=27, crc32=0x5bf7fc04
     - [801081531] OK : tid=1, gop=22, frame=28, crc32=0x2b936f7c
     - [801081531] OK : tid=1, gop=22, frame=29, crc32=0xa1dd9155
 - GOP #23 testing :  Sequence error : 1 expected, but not 22
     - [801081531] OK : tid=1, gop=23, frame=0, crc32=0x53243839
     - [801081578] OK : tid=1, gop=23, frame=22, crc32=0xe47f956f
     - [801081578] OK : tid=1, gop=23, frame=23, crc32=0x74d220e7
     - [801081578] OK : tid=1, gop=23, frame=24, crc32=0x4b6b39f
     - [801081578] OK : tid=1, gop=23, frame=25, crc32=0xbb3edaf4
     - [801081578] OK : tid=1, gop=23, frame=26, crc32=0xcb5a498c
     - [801081578] OK : tid=1, gop=23, frame=27, crc32=0x5bf7fc04
     - [801081578] OK : tid=1, gop=23, frame=28, crc32=0x2b936f7c
     - [801081578] OK : tid=1, gop=23, frame=29, crc32=0xa1dd9155
  - (error) no GOP #24
 - GOP #25 testing :  Sequence error : 1 expected, but not 22
     - [801081578] OK : tid=1, gop=25, frame=0, crc32=0x275caa5e
     - [801081656] OK : tid=1, gop=25, frame=22, crc32=0xe47f956f
     - [801081656] OK : tid=1, gop=25, frame=23, crc32=0x74d220e7
     - [801081656] OK : tid=1, gop=25, frame=24, crc32=0x4b6b39f
     - [801081656] OK : tid=1, gop=25, frame=25, crc32=0xbb3edaf4
     - [801081656] OK : tid=1, gop=25, frame=26, crc32=0xcb5a498c
     - [801081656] OK : tid=1, gop=25, frame=27, crc32=0x5bf7fc04
     - [801081656] OK : tid=1, gop=25, frame=28, crc32=0x2b936f7c
     - [801081656] OK : tid=1, gop=25, frame=29, crc32=0xa1dd9155
 - GOP #27 testing :  Sequence error : 0 expected, but not 22
     - [801081703] OK : tid=1, gop=27, frame=22, crc32=0xe47f956f
     - [801081703] OK : tid=1, gop=27, frame=23, crc32=0x74d220e7
     - [801081703] OK : tid=1, gop=27, frame=24, crc32=0x4b6b39f
     - [801081703] OK : tid=1, gop=27, frame=25, crc32=0xbb3edaf4
     - [801081703] OK : tid=1, gop=27, frame=26, crc32=0xcb5a498c
     - [801081703] OK : tid=1, gop=27, frame=27, crc32=0x5bf7fc04
     - [801081703] OK : tid=1, gop=27, frame=28, crc32=0x2b936f7c
     - [801081703] OK : tid=1, gop=27, frame=29, crc32=0xa1dd9155
 - GOP #29 testing :  Sequence error : 0 expected, but not 22
     - [801081781] OK : tid=1, gop=29, frame=22, crc32=0xe47f956f
     - [801081781] OK : tid=1, gop=29, frame=23, crc32=0x74d220e7
     - [801081781] OK : tid=1, gop=29, frame=24, crc32=0x4b6b39f
     - [801081781] OK : tid=1, gop=29, frame=25, crc32=0xbb3edaf4
     - [801081781] OK : tid=1, gop=29, frame=26, crc32=0xcb5a498c
     - [801081781] OK : tid=1, gop=29, frame=27, crc32=0x5bf7fc04
     - [801081781] OK : tid=1, gop=29, frame=28, crc32=0x2b936f7c
     - [801081781] OK : tid=1, gop=29, frame=29, crc32=0xa1dd9155
 - GOP #30 testing :  Sequence error : 1 expected, but not 22
     - [801081781] OK : tid=1, gop=30, frame=0, crc32=0xf0d8604d
     - [801081828] OK : tid=1, gop=30, frame=22, crc32=0xe47f956f
     - [801081828] OK : tid=1, gop=30, frame=23, crc32=0x74d220e7
     - [801081828] OK : tid=1, gop=30, frame=24, crc32=0x4b6b39f
     - [801081828] OK : tid=1, gop=30, frame=25, crc32=0xbb3edaf4
     - [801081828] OK : tid=1, gop=30, frame=26, crc32=0xcb5a498c
     - [801081828] OK : tid=1, gop=30, frame=27, crc32=0x5bf7fc04
     - [801081828] OK : tid=1, gop=30, frame=28, crc32=0x2b936f7c
     - [801081828] OK : tid=1, gop=30, frame=29, crc32=0xa1dd9155
  - (error) no GOP #31
 - GOP #32 testing :  Sequence error : 1 expected, but not 22
     - [801081828] OK : tid=1, gop=32, frame=0, crc32=0x8db5c968
     - [801081906] OK : tid=1, gop=32, frame=22, crc32=0xe47f956f
     - [801081906] OK : tid=1, gop=32, frame=23, crc32=0x74d220e7
     - [801081906] OK : tid=1, gop=32, frame=24, crc32=0x4b6b39f
     - [801081906] OK : tid=1, gop=32, frame=25, crc32=0xbb3edaf4
     - [801081906] OK : tid=1, gop=32, frame=26, crc32=0xcb5a498c
     - [801081906] OK : tid=1, gop=32, frame=27, crc32=0x5bf7fc04
     - [801081906] OK : tid=1, gop=32, frame=28, crc32=0x2b936f7c
     - [801081906] OK : tid=1, gop=32, frame=29, crc32=0xa1dd9155
 - GOP #33 testing :  Sequence error : 1 expected, but not 22
     - [801081906] OK : tid=1, gop=33, frame=0, crc32=0x2dcfe583
     - [801081921] OK : tid=1, gop=33, frame=22, crc32=0xe47f956f
     - [801081921] OK : tid=1, gop=33, frame=23, crc32=0x74d220e7
     - [801081921] OK : tid=1, gop=33, frame=24, crc32=0x4b6b39f
     - [801081921] OK : tid=1, gop=33, frame=25, crc32=0xbb3edaf4
     - [801081921] OK : tid=1, gop=33, frame=26, crc32=0xcb5a498c
     - [801081921] OK : tid=1, gop=33, frame=27, crc32=0x5bf7fc04
     - [801081921] OK : tid=1, gop=33, frame=28, crc32=0x2b936f7c
     - [801081921] OK : tid=1, gop=33, frame=29, crc32=0xa1dd9155
  - (error) no GOP #34
 - GOP #35 testing :  Sequence error : 1 expected, but not 22
     - [801081921] OK : tid=1, gop=35, frame=0, crc32=0xb64aba14
     - [801082000] OK : tid=1, gop=35, frame=22, crc32=0xe47f956f
     - [801082000] OK : tid=1, gop=35, frame=23, crc32=0x74d220e7
     - [801082000] OK : tid=1, gop=35, frame=24, crc32=0x4b6b39f
     - [801082000] OK : tid=1, gop=35, frame=25, crc32=0xbb3edaf4
     - [801082000] OK : tid=1, gop=35, frame=26, crc32=0xcb5a498c
     - [801082000] OK : tid=1, gop=35, frame=27, crc32=0x5bf7fc04
     - [801082000] OK : tid=1, gop=35, frame=28, crc32=0x2b936f7c
     - [801082000] OK : tid=1, gop=35, frame=29, crc32=0xa1dd9155
  - (error) no GOP #36
 - GOP #39 testing :  Sequence error : 1 expected, but not 22
     - [801082062] OK : tid=1, gop=39, frame=0, crc32=0x5a31037b
     - [801082140] OK : tid=1, gop=39, frame=22, crc32=0xe47f956f
     - [801082140] OK : tid=1, gop=39, frame=23, crc32=0x74d220e7
     - [801082140] OK : tid=1, gop=39, frame=24, crc32=0x4b6b39f
     - [801082140] OK : tid=1, gop=39, frame=25, crc32=0xbb3edaf4
     - [801082140] OK : tid=1, gop=39, frame=26, crc32=0xcb5a498c
     - [801082140] OK : tid=1, gop=39, frame=27, crc32=0x5bf7fc04
     - [801082140] OK : tid=1, gop=39, frame=28, crc32=0x2b936f7c
     - [801082140] OK : tid=1, gop=39, frame=29, crc32=0xa1dd9155
  - (error) no GOP #40
 - GOP #41 testing :  Sequence error : 0 expected, but not 22
     - [801082203] OK : tid=1, gop=41, frame=22, crc32=0xe47f956f
     - [801082203] OK : tid=1, gop=41, frame=23, crc32=0x74d220e7
     - [801082203] OK : tid=1, gop=41, frame=24, crc32=0x4b6b39f
     - [801082203] OK : tid=1, gop=41, frame=25, crc32=0xbb3edaf4
     - [801082203] OK : tid=1, gop=41, frame=26, crc32=0xcb5a498c
     - [801082203] OK : tid=1, gop=41, frame=27, crc32=0x5bf7fc04
     - [801082203] OK : tid=1, gop=41, frame=28, crc32=0x2b936f7c
     - [801082203] OK : tid=1, gop=41, frame=29, crc32=0xa1dd9155
  - (error) no GOP #42
 - GOP #43 testing :  Sequence error : 1 expected, but not 22
     - [801082203] OK : tid=1, gop=43, frame=0, crc32=0xb5ccce8b
     - [801082250] OK : tid=1, gop=43, frame=22, crc32=0xe47f956f
     - [801082250] OK : tid=1, gop=43, frame=23, crc32=0x74d220e7
     - [801082250] OK : tid=1, gop=43, frame=24, crc32=0x4b6b39f
     - [801082250] OK : tid=1, gop=43, frame=25, crc32=0xbb3edaf4
     - [801082250] OK : tid=1, gop=43, frame=26, crc32=0xcb5a498c
     - [801082250] OK : tid=1, gop=43, frame=27, crc32=0x5bf7fc04
     - [801082250] OK : tid=1, gop=43, frame=28, crc32=0x2b936f7c
     - [801082250] OK : tid=1, gop=43, frame=29, crc32=0xa1dd9155
 - GOP #45 testing :  Sequence error : 0 expected, but not 22
     - [801082328] OK : tid=1, gop=45, frame=22, crc32=0xe47f956f
     - [801082328] OK : tid=1, gop=45, frame=23, crc32=0x74d220e7
     - [801082328] OK : tid=1, gop=45, frame=24, crc32=0x4b6b39f
     - [801082328] OK : tid=1, gop=45, frame=25, crc32=0xbb3edaf4
     - [801082328] OK : tid=1, gop=45, frame=26, crc32=0xcb5a498c
     - [801082328] OK : tid=1, gop=45, frame=27, crc32=0x5bf7fc04
     - [801082328] OK : tid=1, gop=45, frame=28, crc32=0x2b936f7c
     - [801082328] OK : tid=1, gop=45, frame=29, crc32=0xa1dd9155
 - GOP #46 testing :  Sequence error : 1 expected, but not 22
     - [801082328] OK : tid=1, gop=46, frame=0, crc32=0xf9cd5b0f
     - [801082375] OK : tid=1, gop=46, frame=22, crc32=0xe47f956f
     - [801082375] OK : tid=1, gop=46, frame=23, crc32=0x74d220e7
     - [801082375] OK : tid=1, gop=46, frame=24, crc32=0x4b6b39f
     - [801082375] OK : tid=1, gop=46, frame=25, crc32=0xbb3edaf4
     - [801082375] OK : tid=1, gop=46, frame=26, crc32=0xcb5a498c
     - [801082375] OK : tid=1, gop=46, frame=27, crc32=0x5bf7fc04
     - [801082375] OK : tid=1, gop=46, frame=28, crc32=0x2b936f7c
     - [801082375] OK : tid=1, gop=46, frame=29, crc32=0xa1dd9155
  - (error) no GOP #47
 - GOP #48 testing :  time error : done=801082421ms < frame=801082703ms
     - [801082375] OK : tid=1, gop=48, frame=0, crc32=0x8ab92056
     - [801082703] OK : tid=1, gop=48, frame=1, crc32=0xe5756332
     - [801082703] OK : tid=1, gop=48, frame=2, crc32=0x9511f04a
     - [801082703] OK : tid=1, gop=48, frame=3, crc32=0x5bc45c2
     - [801082703] OK : tid=1, gop=48, frame=4, crc32=0x75d8d6ba
     - [801082703] OK : tid=1, gop=48, frame=5, crc32=0xff962893
     - [801082703] OK : tid=1, gop=48, frame=6, crc32=0x8ff2bbeb
     - [801082703] OK : tid=1, gop=48, frame=7, crc32=0x1f5f0e63
     - [801082703] OK : tid=1, gop=48, frame=8, crc32=0x6f3b9d1b
     - [801082703] OK : tid=1, gop=48, frame=9, crc32=0xd0b3f470
     - [801082703] OK : tid=1, gop=48, frame=10, crc32=0xa0d76708
     - [801082703] OK : tid=1, gop=48, frame=11, crc32=0x307ad280
     - [801082703] OK : tid=1, gop=48, frame=12, crc32=0x401e41f8
     - [801082703] OK : tid=1, gop=48, frame=13, crc32=0xca50bfd1
     - [801082703] OK : tid=1, gop=48, frame=14, crc32=0xba342ca9
     - [801082703] OK : tid=1, gop=48, frame=15, crc32=0x2a999921
     - [801082703] OK : tid=1, gop=48, frame=16, crc32=0x5afd0a59
     - [801082703] OK : tid=1, gop=48, frame=17, crc32=0x8ef84db6
     - [801082703] OK : tid=1, gop=48, frame=18, crc32=0xfe9cdece
     - [801082703] OK : tid=1, gop=48, frame=19, crc32=0x6e316b46
     - [801082703] OK : tid=1, gop=48, frame=20, crc32=0x1e55f83e
     - [801082703] OK : tid=1, gop=48, frame=21, crc32=0x941b0617
     - [801082703] OK : tid=1, gop=48, frame=22, crc32=0xe47f956f
     - [801082703] OK : tid=1, gop=48, frame=23, crc32=0x74d220e7
     - [801082703] OK : tid=1, gop=48, frame=24, crc32=0x4b6b39f
     - [801082703] OK : tid=1, gop=48, frame=25, crc32=0xbb3edaf4
     - [801082703] OK : tid=1, gop=48, frame=26, crc32=0xcb5a498c
     - [801082703] OK : tid=1, gop=48, frame=27, crc32=0x5bf7fc04
     - [801082703] OK : tid=1, gop=48, frame=28, crc32=0x2b936f7c
     - [801082703] OK : tid=1, gop=48, frame=29, crc32=0xa1dd9155
 - GOP #49 testing :  time error : done=801082421ms < frame=801082703ms
     - [801082703] OK : tid=1, gop=49, frame=0, crc32=0x2ac30cbd
     - [801082812] OK : tid=1, gop=49, frame=1, crc32=0xe5756332
     - [801082812] OK : tid=1, gop=49, frame=2, crc32=0x9511f04a
     - [801082812] OK : tid=1, gop=49, frame=3, crc32=0x5bc45c2
     - [801082812] OK : tid=1, gop=49, frame=4, crc32=0x75d8d6ba
     - [801082812] OK : tid=1, gop=49, frame=5, crc32=0xff962893
     - [801082812] OK : tid=1, gop=49, frame=6, crc32=0x8ff2bbeb
     - [801082812] OK : tid=1, gop=49, frame=7, crc32=0x1f5f0e63
     - [801082812] OK : tid=1, gop=49, frame=8, crc32=0x6f3b9d1b
     - [801082812] OK : tid=1, gop=49, frame=9, crc32=0xd0b3f470
     - [801082812] OK : tid=1, gop=49, frame=10, crc32=0xa0d76708
     - [801082812] OK : tid=1, gop=49, frame=11, crc32=0x307ad280
     - [801082812] OK : tid=1, gop=49, frame=12, crc32=0x401e41f8
     - [801082812] OK : tid=1, gop=49, frame=13, crc32=0xca50bfd1
     - [801082812] OK : tid=1, gop=49, frame=14, crc32=0xba342ca9
     - [801082812] OK : tid=1, gop=49, frame=15, crc32=0x2a999921
     - [801082812] OK : tid=1, gop=49, frame=16, crc32=0x5afd0a59
     - [801082812] OK : tid=1, gop=49, frame=17, crc32=0x8ef84db6
     - [801082812] OK : tid=1, gop=49, frame=18, crc32=0xfe9cdece
     - [801082812] OK : tid=1, gop=49, frame=19, crc32=0x6e316b46
     - [801082812] OK : tid=1, gop=49, frame=20, crc32=0x1e55f83e
     - [801082812] OK : tid=1, gop=49, frame=21, crc32=0x941b0617
     - [801082812] OK : tid=1, gop=49, frame=22, crc32=0xe47f956f
     - [801082812] OK : tid=1, gop=49, frame=23, crc32=0x74d220e7
     - [801082812] OK : tid=1, gop=49, frame=24, crc32=0x4b6b39f
     - [801082812] OK : tid=1, gop=49, frame=25, crc32=0xbb3edaf4
     - [801082812] OK : tid=1, gop=49, frame=26, crc32=0xcb5a498c
     - [801082812] OK : tid=1, gop=49, frame=27, crc32=0x5bf7fc04
     - [801082812] OK : tid=1, gop=49, frame=28, crc32=0x2b936f7c
     - [801082812] OK : tid=1, gop=49, frame=29, crc32=0xa1dd9155
============================================
         RESULT
============================================
 - CMD time diff= 1.75s (801080671 ~ 801082421)
 - expect : frames=1500
 - received : frames=627, fps=358.29
 - loss frames=873, ratio= 58.2%
 - DONE
[C2C_NOANSWER]
NTIL_TerminateConnection(0)
```