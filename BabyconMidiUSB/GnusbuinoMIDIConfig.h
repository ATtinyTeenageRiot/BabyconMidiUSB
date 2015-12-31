//
// Misc Options.. 
//

//#define GNUSBUINOMIDI_ENABLE_ANDROID		//hack to make device compatible with android device but broke on windows
//#define GNUSBUINOMIDI_WITH_AUDIO_CONTROL	//enable virtual dummy audio device

//
// Custom USB D+ and D- pin
//

/*

#define GNUSBUINOMIDI_ENABLE_CUSTOM_USB_CFG
#define GNUSBUINOMIDI_USB_IOPORTNAME B	//when custom cfg disabled default is B
#define GNUSBUINOMIDI_USB_DMINUS 5	//when custom cfg disabled default is 5
#define GNUSBUINOMIDI_USB_DPLUS 3	//when custom cfg disabled default is 3

*/

//
// Same as default interrupt config
//

/*

#define GNUSBUINOMIDI_ENABLE_CUSTOM_DPLUS_INTERRUPT
#define GNUSBUINOMIDI_USB_INTR_CFG            PCMSK
#define GNUSBUINOMIDI_USB_INTR_CFG_SET        (1 << USB_CFG_DPLUS_BIT)
#define GNUSBUINOMIDI_USB_INTR_CFG_CLR        0
#define GNUSBUINOMIDI_USB_INTR_ENABLE         GIMSK
#define GNUSBUINOMIDI_USB_INTR_ENABLE_BIT     PCIE
#define GNUSBUINOMIDI_USB_INTR_PENDING        GIFR
#define GNUSBUINOMIDI_USB_INTR_PENDING_BIT    PCIF
#define GNUSBUINOMIDI_USB_INTR_VECTOR         PCINT0_vect    	

*/