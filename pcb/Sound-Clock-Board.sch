EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_01x20 J1
U 1 1 5FC06139
P 3200 4550
F 0 "J1" H 3280 4542 50  0000 L CNN
F 1 "ESPThingLeftSide" H 3280 4451 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x20_P2.54mm_Vertical" H 3200 4550 50  0001 C CNN
F 3 "~" H 3200 4550 50  0001 C CNN
	1    3200 4550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x20 J2
U 1 1 5FC07656
P 6500 4600
F 0 "J2" H 6580 4592 50  0000 L CNN
F 1 "ESPThingRightSide" H 6580 4501 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x20_P2.54mm_Vertical" H 6500 4600 50  0001 C CNN
F 3 "~" H 6500 4600 50  0001 C CNN
	1    6500 4600
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x07 J3
U 1 1 5FC0835B
P 4650 2950
F 0 "J3" V 4522 3330 50  0000 L CNN
F 1 "I2SBoard" V 4613 3330 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 4650 2950 50  0001 C CNN
F 3 "~" H 4650 2950 50  0001 C CNN
	1    4650 2950
	0    1    1    0   
$EndComp
Wire Wire Line
	3000 5250 4850 5250
Wire Wire Line
	4850 5250 4850 2750
Wire Wire Line
	3000 4650 4450 4650
Wire Wire Line
	4450 4650 4450 2750
Wire Wire Line
	3000 4550 4350 4550
Wire Wire Line
	4350 4550 4350 2750
Wire Wire Line
	3000 4450 4550 4450
Wire Wire Line
	4550 4450 4550 2750
Wire Wire Line
	6300 5300 7750 5300
Wire Wire Line
	7750 5300 7750 4600
Wire Wire Line
	6300 5100 7600 5100
Wire Wire Line
	7600 5100 7600 4500
Wire Wire Line
	7600 4500 7750 4500
Wire Wire Line
	6300 4900 7350 4900
Wire Wire Line
	7350 4900 7350 4400
Wire Wire Line
	7350 4400 7750 4400
$Comp
L Connector_Generic:Conn_01x03 J4
U 1 1 5FC97F1D
P 7950 4500
F 0 "J4" H 8030 4542 50  0000 L CNN
F 1 "Touch sensor and config switch" H 8030 4451 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7950 4500 50  0001 C CNN
F 3 "~" H 7950 4500 50  0001 C CNN
	1    7950 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 5150 4950 2750
Wire Wire Line
	3000 5150 4950 5150
Wire Wire Line
	3000 4850 3850 4850
Wire Wire Line
	3000 4950 4650 4950
Wire Wire Line
	4650 4950 4650 4850
$Comp
L Device:R_Small_US R1
U 1 1 5FCA8101
P 3950 4850
F 0 "R1" V 3745 4850 50  0000 C CNN
F 1 "R_Small_US" V 3836 4850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" H 3950 4850 50  0001 C CNN
F 3 "~" H 3950 4850 50  0001 C CNN
	1    3950 4850
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 4850 4650 4850
Connection ~ 4650 4850
Wire Wire Line
	4650 4850 4650 2750
$EndSCHEMATC
