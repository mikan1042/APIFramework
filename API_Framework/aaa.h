#pragma once


// ** 함수참고 ** //
/*
TransparentBlt 

hdcDest						// ** 핸들
xoriginDest, yoriginDest	// ** 출력할 위치 X,Y
wDest, hDest				// ** 출력할 이미지의 크기 
hdcSrc						// ** 이미지의 핸들
xoriginSrc, yoriginSrc		// ** 이미지의 시작지점 
wSrc, hSrc					// ** 잘라낼 크기
crTransparent				// ** 마젠타색상

*/


// ** 가장 최근에 완료한 작업 ** //
/*
* 
* 	** Player가 유카리일 경우 유카리 앞에 공격 요괴를 생성
*   ** X키를 누를경우 요정생성 (임시)
*	** Logo화면에 이미지 출력

※※※ GetTickCount64를 이용하여 총알발사에 딜레이를 주려고 했으나
게임 전체에 딜레이가 적용되어 잠시 보류 ( 해결완료 )

※※※ 요정과 탄막간의 충돌이 일어나지않아서 수정 예정


*/








// 실제작업한 날은 하루 전 날짜 (엑셀 양식과 맞추기 위함)

// ** 9월 27일 ** //
/*
	** Player가 유카리일 경우 유카리 앞에 공격 요괴를 생성


	※ 문제점
	 - 공격에 딜레이를 주려고 했으나 게임 전체가 멈추는 현상 (해결완료)
*/

// ** 9월 26일 ** //
/*				
	** 게임에서 정보를 알려주는 UI를 제작 및 출력 (리소스를 구하지 못함)(시간지체)
	** Player가 이동할 수 있는 구역을 제한 (화면밖으로 나가지 않게하기를 위함)
	** Player의 시작 위치 재설정
	
	※ 문제점
	 - 공격에 딜레이를 주려고 했으나 게임 전체가 멈추는 현상
*/

// ** 9월 25일 ** //
/*					
	** Player의 공격을 출력하고 충돌 시 탄막과 몬스터의 제거를 구현
	** 탄막이 화면을 벗어날 경우 탄막을 제거
	** Shift를 토글하고 있을 경우 Player의 이미지 변경 (레이무 -> 유카리)
	** Player가 유카리일 경우 공격과 이동속도를 변화
*/

// ** 9월 24일 ** //		
/*					
	** 기본적인 프레임워크를 작성함
	** Player의 캐릭터(레이무)를 생성
	** Player의 이동을 구현
*/