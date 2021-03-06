#pragma once
#define JOYSTICK_LEFT 323
#define JOYSTICK_RIGHT 324
#define JOYSTICK_UP 325
#define JOYSTICK_DOWN 326
#define JOYSTICK_BUTTON 327
#define MOUSE_BUTTON 346

static char* SDLKeyStrings[] = {
	"UNKNOWN",					//0
	"",							//1
	"",							//2
	"",							//3
	"",							//4
	"",							//5
	"",							//6
	"",							//7
	"BACKSPACE",				//8
	"TAB",						//9
	"",							//10
	"",							//11
	"CLEAR",					//12
	"RETURN",					//13
	"",							//14
	"",							//15
	"",							//16
	"",							//17
	"",							//18
	"PAUSE",					//19
	"",							//20
	"",							//21
	"",							//22
	"",							//23
	"",							//24
	"",							//25
	"",							//26
	"ESCAPE",					//27
	"",							//28
	"",							//29
	"",							//30
	"",							//31
	"SPACE",					//32
	"EXCLAIM",					//33
	"QUOTEDBL",					//34
	"HASH",						//35
	"DOLLAR",					//36
	"",							//37
	"AMPERSAND",				//38
	"QUOTE",					//39
	"LEFTPAREN",				//40
	"RIGHTPAREN",				//41
	"ASTERISK",					//42
	"PLUS",						//43
	"COMMA",					//44
	"MINUS",					//45
	"PERIOD",					//46
	"SLASH",					//47
	"0",						//48
	"1",						//49
	"2",						//50
	"3",						//51
	"4",						//52
	"5",						//53
	"6",						//54
	"7",						//55
	"8",						//56
	"9",						//57
	"COLON",					//58
	"SEMICOLON",				//59
	"LESS",						//60
	"EQUALS",					//61
	"GREATER",					//62
	"QUESTION",					//63
	"AT",						//64
#ifdef USE_SDL2
	"","","","","","","","",
	"INSERT",					//73
	"HOME",						//74
	"PAGE UP",					//75
	"DELETE",					//76
	"END",						//77
	"PAGE DOWN",				//78
	"RIGHT",					//79
	"LEFT",						//80
	"DOWN",						//81
	"UP",						//82
	"",	"","","","","","","",
#else
	"","","","","","","","","","","","","","","","","","","","","","","","","","",
#endif
	"LEFTBRACKET",				//91
	"BACKSLASH",				//92
	"RIGHTBRACKET",				//93
	"CARET",					//94
	"UNDERSCORE",				//95
	"BACKQUOTE",				//96
	"A",						//97
	"B",						//98
	"C",						//99
	"D",						//100
	"E",						//101
	"F",						//102
	"G",						//103
	"H",						//104
	"I",						//105
	"J",						//106
	"K",						//107
	"L",						//108
	"M",						//109
	"N",						//110
	"O",						//111
	"P",						//112
	"Q",						//113
	"R",						//114
	"S",						//115
	"T",						//116
	"U",						//117
	"V",						//118
	"W",						//119
	"X",						//120
	"Y",						//121
	"Z",						//122
	"","","","",				//
	"DELETE",					//127
	"","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","",
	"WORLD_0",					//160
	"WORLD_1",					//161
	"WORLD_2",					//162
	"WORLD_3",					//163
	"WORLD_4",					//164
	"WORLD_5",					//165
	"WORLD_6",					//166
	"WORLD_7",					//167
	"WORLD_8",					//168
	"WORLD_9",					//169
	"WORLD_10",					//170
	"WORLD_11",					//171
	"WORLD_12",					//172
	"WORLD_13",					//173
	"WORLD_14",					//174
	"WORLD_15",					//175
	"WORLD_16",					//176
	"WORLD_17",					//177
	"WORLD_18",					//178
	"WORLD_19",					//179
	"WORLD_20",					//180
	"WORLD_21",					//181
	"WORLD_22",					//182
	"WORLD_23",					//183
	"WORLD_24",					//184
	"WORLD_25",					//185
	"WORLD_26",					//186
	"WORLD_27",					//187
	"WORLD_28",					//188
	"WORLD_29",					//189
	"WORLD_30",					//190
	"WORLD_31",					//191
	"WORLD_32",					//192
	"WORLD_33",					//193
	"WORLD_34",					//194
	"WORLD_35",					//195
	"WORLD_36",					//196
	"WORLD_37",					//197
	"WORLD_38",					//198
	"WORLD_39",					//199
	"WORLD_40",					//200
	"WORLD_41",					//201
	"WORLD_42",					//202
	"WORLD_43",					//203
	"WORLD_44",					//204
	"WORLD_45",					//205
	"WORLD_46",					//206
	"WORLD_47",					//207
	"WORLD_48",					//208
	"WORLD_49",					//209
	"WORLD_50",					//210
	"WORLD_51",					//211
	"WORLD_52",					//212
	"WORLD_53",					//213
	"WORLD_54",					//214
	"WORLD_55",					//215
	"WORLD_56",					//216
	"WORLD_57",					//217
	"WORLD_58",					//218
	"WORLD_59",					//219
	"WORLD_60",					//220
	"WORLD_61",					//221
	"WORLD_62",					//222
	"WORLD_63",					//223
#ifdef USE_SDL2
	"L CTRL",					//224
	"L SHIFT",					//225
	"L ALT",					//226
	"WORLD_67",					//227
	"R CTRL",					//228
	"R SHIFT",					//229
#else
	"WORLD_64",					//224
	"WORLD_65",					//225
	"WORLD_66",					//226
	"WORLD_67",					//227
	"WORLD_68",					//228
	"WORLD_69",					//229
#endif
	"WORLD_70",					//230
	"WORLD_71",					//231
	"WORLD_72",					//232
	"WORLD_73",					//233
	"WORLD_74",					//234
	"WORLD_75",					//235
	"WORLD_76",					//236
	"WORLD_77",					//237
	"WORLD_78",					//238
	"WORLD_79",					//239
	"WORLD_80",					//240
	"WORLD_81",					//241
	"WORLD_82",					//242
	"WORLD_83",					//243
	"WORLD_84",					//244
	"WORLD_85",					//245
	"WORLD_86",					//246
	"WORLD_87",					//247
	"WORLD_88",					//248
	"WORLD_89",					//249
	"WORLD_90",					//250
	"WORLD_91",					//251
	"WORLD_92",					//252
	"WORLD_93",					//253
	"WORLD_94",					//254
	"WORLD_95",					//255
	"KEYPAD0",					//256
	"KEYPAD1",					//257
	"KEYPAD2",					//258
	"KEYPAD3",					//259
	"KEYPAD4",					//260
	"KEYPAD5",					//261
	"KEYPAD6",					//262
	"KEYPAD7",					//263
	"KEYPAD8",					//264
	"KEYPAD9",					//265
	"KEYPAD PERIOD",			//266
	"KEYPAD DIVIDE",			//267
	"KEYPAD MULTIPLY",			//268
	"KEYPAD MINUS",				//269
	"KEYPAD PLUS",				//270
	"KEYPAD ENTER",				//271
	"KEYPAD EQUALS",			//272
	"UP",						//273
	"DOWN",						//274
	"RIGHT",					//275
	"LEFT",						//276
	"INSERT",					//277
	"HOME",						//278
	"END",						//279
	"PAGEUP",					//280
	"PAGEDOWN",					//281
	"F1",						//282
	"F2",						//283
	"F3",						//284
	"F4",						//285
	"F5",						//286
	"F6",						//287
	"F7",						//288
	"F8",						//289
	"F9",						//290
	"F10",						//291
	"F11",						//292
	"F12",						//293
	"F13",						//294
	"F14",						//295
	"F15",						//296
	"","","",					//
	"NUMLOCK",					//300
	"CAPSLOCK",					//301
	"SCROLLOCK",				//302
	"RIGHT SHIFT",				//303
	"LEFT SHIFT",				//304
	"RIGHT CTRL",				//305
	"LEFT CTRL",				//306
	"RIGHT ALT",				//307
	"LEFT ALT",					//308
	"RIGHT META",				//309
	"LEFT META",				//310
	"LEFT SUPER",				//311
	"RIGHT SUPER",				//312
	"MODE",						//313
	"COMPOSE",					//314
	"HELP",						//315
	"PRINT",					//316
	"SYSREQ",					//317
	"BREAK",					//318
	"MENU",						//319
	"POWER",					//320
	"EURO",						//321
	"UNDO",						//322
	"JOYLEFT",					//323
	"JOYRIGHT",					//324
	"JOYUP",					//325
	"JOYDOWN",					//326
	"JOYBUTTON1",				//327
	"JOYBUTTON2",				//328
	"JOYBUTTON3",				//329
	"JOYBUTTON4",				//330
	"JOYBUTTON5",				//331
	"JOYBUTTON6",				//332
	"JOYBUTTON7",				//333
	"JOYBUTTON8",				//334
	"JOYBUTTON9",				//335
	"JOYBUTTON10",				//336
	"JOYBUTTON11",				//337
	"JOYBUTTON12",				//338
	"JOYBUTTON13",				//339
	"JOYBUTTON14",				//340
	"JOYBUTTON15",				//341
	"JOYBUTTON16",				//342
	"JOYBUTTON17",				//343
	"JOYBUTTON18",				//344
	"JOYBUTTON19",				//345
	"JOYBUTTON20",				//346
	"MOUSE1",					//347
	"MOUSE2",					//348
	"MOUSE3",					//349
	"MOUSE4",					//350
	"MOUSE5",					//351
	"MOUSE6",					//352
	"MOUSE7",					//353
	"MOUSE8",					//354
	"MOUSE9",					//355
	"MOUSE10"					//356
	};
