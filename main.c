/* 
 * File:   main.c
 * Author: Tool Labs
 * プログラム内容:
 * 　　タクトスイッチ(GP4)が押されたら、
 * 　　発光ダイオードをトグルする。
 * 　　これは、うまく動かないバージョン。
 */

// インクルードファイル
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

// PIC12F683コンフィグレーションビット設定
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Detect (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)

// クロック周波数指定 (ここでは8MHzに設定)
// (__delay_ms()関数が必要としているため)
#define _XTAL_FREQ  1000000

/*
 * main()関数
 */
int main(int argc, char** argv) {

    // PICマイコン初期化
    OSCCON = 0x40;  //クロック周波数を1MHzに設定
    ANSEL  = 0x00;  //すべてのピンをデジタルモードに設定
    TRISIO = 0x10;  //GP4を入力ピン、それ以外を出力ピンに設定。ただしGP3ピンはもともと入力固定

    // タイマー用の変数
    unsigned char timer;

    // ブザーのピン(GP2)を0にして、ブザーをOFFにする
    GP2 = 0;

    // LEDのピン(GP5)を1にして、LEDを点灯させる
    GP5 = 1;

    // スイッチ(GP3)がOFFの間、何もしないで待ち続ける
    while(GP3){
    }

    // スイッチが押されたら、LEDの点滅を開始する
    // まずはじめにLEDのピン(GP5)を0にして、LEDを消灯する
    GP5 = 0;

    // 1秒点滅を10回繰り返す。つまり10秒間点滅させる
    for(timer=0; timer<10; timer++) {
        // まず、消灯状態のまま950ミリ秒待つ
        __delay_ms(950);
        // 950ミリ秒経過したら、LEDのピンを1にして、LEDを点灯する
        GP5 = 1;
        // LED点灯状態で50ミリ秒待つ
        __delay_ms(50);
        // 50ミリ秒経ったら、LEDのピンを0にして、LEDを消灯する
        GP5 = 0;
    }

    // ブザーのピン(GP2)を1にして、ブザーをならす
    GP2 = 1;

    // LEDのピン(GP5)を1にして、LEDを点灯させる
    GP5 = 1;

    // そのままの状態にする
    while(1){
    }

    // ここには到達しない
    return (EXIT_SUCCESS);
}

