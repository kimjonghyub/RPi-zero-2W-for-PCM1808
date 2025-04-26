#!/bin/bash

# 48000Hz로 입력 받고 48000Hz로 출력
# 인터럽트 (Ctrl+C) 시 안전하게 프로세스 종료 처리

# 녹음 -> 변환 -> 재생 전체 파이프라인
arecord -D hw:0,0 -f S32_LE -r 48000 -c 2 | \
sox -t raw -e signed -b 32 -c 2 -r 48000 - -t raw -e signed -b 16 -c 2 -r 48000 - | \
aplay -D hw:1,0 -f S16_LE -r 48000 -c 2 &

# 백그라운드 PID 저장
PID=$!

# Ctrl+C (SIGINT) 캡처해서 종료
trap "echo ''; echo '정리 중...'; kill $PID; wait $PID 2>/dev/null; echo '정상 종료되었습니다.'; exit 0" SIGINT

# 무한 대기 (프로세스 유지)
wait $PID
