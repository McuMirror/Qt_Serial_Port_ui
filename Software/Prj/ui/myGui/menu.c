#include "menu.h"
#include "stdio.h"

u8g2_t u8g2;

/*
  ����Ŀģ�������;���δ��Դ�� MonoUI������ʵ������ UltraLink ��˿������
    * �ֱ��� 128 * 64 �����˵�ģ�� UltraLink ������ƣ�ȥ����С���⣬��ѹ����ҳ������ƣ����ڱ���ҳ���Ϊ�б��б������˸÷ֱ���
  WouoUI v2.2 �������ݣ�
    * �Ż��������������������󲻻��ٽ���������ĸ���������
  WouoUI v2 ���ܣ�
    * ȫ��ʹ�÷����Ե�ƽ�����������������б�����������������
    * �Ż�ƽ�������㷨��ֻ�����У��������ƽ��Ȩ�أ�����ÿ��Ȩ��ֵ���ֱ�ɵ�
    * ���Դ�ϵķ����Զ�������ǰ����δ��������һ�ζ����Ѿ�������ʱ������������Ȼ����
    * ��ͨ�ð汾�ֱ����������� UltraLink ���˵��Ĵ������棨��Ϊ�������� WP7 �� Metron ������Գ�֮Ϊ������
    * ͨ�ð汾�������б�����棬�������޸Ŀ����������зֱ��ʵ���Ļ��������Ļ�������������������
    * �б�˵����б���������ӳ�
    * �б�����ѡ���ѡ���ɸ���ѡ����ַ��������Զ�����������˵�ʱ���б�ͷ�ӳ��� 0 չ����ת����һ���б�ʱ�����Ⱥ�������ƽ���ƶ�����һ��ѡ���λ��
    * �б�ѡ�򣬴�������ʱҲ�����ֵ���б������ڵ�λ�ã�չ���б�ʱ����ÿ�п�ͷ���ַ��ж��Ƿ��������ٸ���λ�������ж��Ƿ��������ĵ�
    * �б��ѡ�򣬴������ݵ��������ѡ���б��������Ӧ����Ҫ���������У�չ���б�ʱ����ÿ�п�ͷ���ַ��ж��Ƿ��������ٸ���������Ӧ�Ĵ�������λ�õ���ֵ�Ƿ�Ϊ1�ж��Ƿ��������ĵ�
    * �б���ʾ��ֵ�����ѡ��ԭ�����ƣ������漰�޸Ĳ���
    * �б�չ����������ʼ���б�ʱ������ѡ���б��ͷ��ʼչ�������ߴ��ϴ�ѡ�е�λ��չ��
    * ͼ��չ����������ʼ�����������ʱ������ѡ��ͼ���ͷ��ʼչ�������ߴ��ϴ�ѡ�е�λ��չ��
    * �������ڣ�ʵ���˴��ڵ����Ķ���Ч���������Զ������ֵ����Сֵ������ֵ����Ҫ�޸ĵĲ����ȣ����ڶ������У����÷ǳ���
    * �������ڱ����黯��ѡ������黯��������ٸУ���ɾ��������Щ��ϧ��������ɿ�ѡ�Ĭ�Ϲر�
    * ���ȵ��ڣ��ڵ��������е�������ֵ����ʵʱ�ı䵱ǰ����ֵ
    * ��ť���ܣ�ʹ��EC11��ť���ƣ���ť��������������������һ��USB���Ƶ��Ե�ʾ������˯��ģʽ����ת���������������ȣ��̰�����һ����ֵ�������������˵�����ť����ʱ���Ȳ��������ڵ��������е���
    * ѭ��ģʽ��ѡ�����ͷβʱ��ѡ������ת����һ��������б�ʹ�������Էֱ�ѡ��
    * �ڰ�ģʽ����ʵ�������Ǻڰ�ģʽ���������˰���ģʽ��Ĭ�Ͽ����ڰ�ģʽ
    * ��ʧ������������ģʽ��һ���ǽ����ȫ�ڣ���һ�ֽ����ȫ��
    * �ϵ�洢���ü�ֱ�۵ķ�ʽ��ÿ�ֹ��ܲ���д��EEPROM��ֻ���޸Ĺ�����������˯��ģʽʱд�룬�����ظ���д����ʼ��ʱ���11����־λ������һλ����

  ��Ŀ�ο���
    * Bվ��·��Ҫʲô���г������߷��棺https://wokwi.com/projects/350306511434547796��https://www.bilibili.com/video/BV1HA411S7pv/
    * Github��createskyblue��OpenT12��https://github.com/createskyblue/OpenT12
    * Github��peng-zhihui��OpenHeat��https://github.com/peng-zhihui/OpenHeat
*/

///************************************* ҳ����� *************************************/
struct
{
    uint8_t line_n; // = DISP_H / LIST_LINE_H;
    int16_t temp;
    bool loop;
    float y;
    float y_trg;
    float box_x;
    float box_x_trg;
    float box_y;
    float box_y_trg[UI_DEPTH];
    float bar_y;
    float bar_y_trg;
} list;


//��ѹ����ҳ�����
//������ģ������
//�������
#define   WAVE_SAMPLE         1                          //�ɼ�����
#define   WAVE_W              94                          //���ο��
#define   WAVE_L              24                          //������߾�
#define   WAVE_U              0                           //�����ϱ߾�
#define   WAVE_MAX            27                          //���ֵ
#define   WAVE_MIN            4                           //��Сֵ
#define   WAVE_BOX_H          32                          //���α߿�߶�
#define   WAVE_BOX_W          94                          //���α߿���
#define   WAVE_BOX_L_S        24                          //���α߿���߾�
//�б�����ֱ��������
#define   VOLT_FONT           u8g2_font_helvB18_tr        //��ѹ��������
#define   VOLT_TEXT_BG_L_S    24                          //���ֱ�������߾�
#define   VOLT_TEXT_BG_W      94                          //���ֱ�������
#define   VOLT_TEXT_BG_H      29                          //���ֱ�����߶�

struct
{
    int     ch0_adc[WAVE_SAMPLE * WAVE_W];
    int     ch0_wave[WAVE_W];
    float   val;
    float   text_bg_r;
    float   text_bg_r_trg;
} volt;


// ѡ������
// Ĭ�ϲ���
#define CHECK_BOX_L_S 95 // ѡ�����ÿ�е���߾�
#define CHECK_BOX_U_S 5  // ѡ�����ÿ�е��ϱ߾�
#define CHECK_BOX_F_W 12 // ѡ��������
#define CHECK_BOX_F_H 12 // ѡ������߶�
#define CHECK_BOX_D_S 2  // ѡ�������ĵ�������ı߾�

// ��խ�и߶Ȳ���
/*
#define CHECK_BOX_L_S 99 // ѡ�����ÿ�е���߾�
#define CHECK_BOX_U_S 0  // ѡ�����ÿ�е��ϱ߾�
#define CHECK_BOX_F_W 5  // ѡ��������
#define CHECK_BOX_F_H 5  // ѡ������߶�
#define CHECK_BOX_D_S 1  // ѡ�������ĵ�������ı߾�
*/

struct
{
    uint8_t *v;
    uint8_t *m;
    uint8_t *s;
    uint8_t *s_p;
} check_box;

// ��������
#define WIN_FONT u8g2_font_HelvetiPixel_tr // ��������
#define WIN_H 32                           // �����߶�
#define WIN_W 102                          // �������
#define WIN_BAR_W 92                       // �������������
#define WIN_BAR_H 7                        // �����������߶�
#define WIN_Y -WIN_H - 2                   // ������ֱ���������ʼλ��
#define WIN_Y_TRG -WIN_H - 2               // ������ֱ�����˳���ֹλ��

// ȷ�ϵ�������
#define CON_WIN_FONT u8g2_font_HelvetiPixel_tr // ��������
#define CON_WIN_H 35                           // �����߶�
#define CON_WIN_W 102                          // �������
#define CON_WIN_Y -CON_WIN_H - 2               // ������ֱ���������ʼλ��
#define CON_WIN_Y_TRG -CON_WIN_H - 2           // ������ֱ�����˳���ֹλ��

struct
{
    uint8_t *value;
    uint8_t max;
    uint8_t min;
    uint8_t step;

    M_SELECT *bg;
    uint8_t index;
    char title[20];
    uint8_t select;
    uint8_t l; // = (DISP_W - WIN_W) / 2;
    uint8_t u; // = (DISP_H - WIN_H) / 2;
    float bar;
    float bar_trg;
    float y;
    float y_trg;
} win;

struct
{
    uint8_t select_btn;
    uint8_t reset_value;
    fun_callback_t cb;
    M_SELECT *bg;
    uint8_t index;
    char title[10];
    uint8_t l; // = (DISP_W - CONFIRM_WIN_W) / 2;
    uint8_t u; // = (DISP_H - CONFIRM_WIN_H) / 2;
    float y;
    float y_trg;
    float btn_x;
    float btn_x_trg;
} con_win;

// ��ť���ܱ���
#define KNOB_PARAM 4
#define KNOB_DISABLE 0
#define KNOB_ROT_VOL 1
#define KNOB_ROT_BRI 2

enum
{
    KNOB_ROT,   // ˯������ת��ť�Ĺ��ܣ�0 ���ã�1 ������2 ����
    KNOB_COD,   // ˯���¶̰���ť������ַ��룬0 ����
    KNOB_ROT_P, // ��ת��ť�����ڵ�ѡ����ѡ���λ��
    KNOB_COD_P, // �ַ����ڵ�ѡ����ѡ���λ��
};
struct
{
    uint8_t param[KNOB_PARAM]; // = {KNOB_DISABLE, KNOB_DISABLE, 2, 2}; // �������б�ĵ�2��ѡ���0���Ǳ��⣬��1���Ƿֽ���
} knob;

uint8_t *buf_ptr; // ָ����Ļ�����ָ��
uint16_t buf_len; // ���峤��

M_UI ui;
M_TILE tile;
M_BTN_INFO btn;
uint8_t eeprom_change = false;

/************************************* �������� *************************************/

/************************************* �������� *************************************/
//��ӽ����һ���� �����˵�
M_SELECT main_menu[] =
        {
                {"Sleep"},
                {"Editor"},
                {"Volt"},
                {"Serial"},
                {"Settings"},
        };

M_SELECT editor_menu[] =
        {
                {"[ Editor ]"},
                {"- Function 0"},
                {"- Function 1"},
                {"- Function 2"},
                {"- Function 3"},
                {"- Function 4"},
                {"- Function 5"},
                {"- Function 6"},
                {"- Function 7"},
                {"- Function 8"},
                {"- Function 9"},
                {"- Knob"},
        };

M_SELECT knob_menu[] =
        {
                {"[ Knob ]"},
                {"# Rotate Func"},
                {"$ Press Func"},
        };

M_SELECT krf_menu[] =
        {
                {"[ Rotate Function ]"},
                {"--------------------------"},
                {"= Disable"},
                {"--------------------------"},
                {"= Volume"},
                {"= Brightness"},
                {"--------------------------"},
        };

M_SELECT kpf_menu[] =
        {
                {"[ Press Function ]"},
                {"--------------------------"},
                {"= Disable"},
                {"--------------------------"},
                {"= A"},
                {"= B"},
                {"= C"},
                {"= D"},
                {"= E"},
                {"= F"},
                {"= G"},
                {"= H"},
                {"= I"},
                {"= J"},
                {"= K"},
                {"= L"},
                {"= M"},
                {"= N"},
                {"= O"},
                {"= P"},
                {"= Q"},
                {"= R"},
                {"= S"},
                {"= T"},
                {"= U"},
                {"= V"},
                {"= W"},
                {"= X"},
                {"= Y"},
                {"= Z"},
                {"--------------------------"},
                {"= 0"},
                {"= 1"},
                {"= 2"},
                {"= 3"},
                {"= 4"},
                {"= 5"},
                {"= 6"},
                {"= 7"},
                {"= 8"},
                {"= 9"},
                {"--------------------------"},
                {"= Esc"},
                {"= F1"},
                {"= F2"},
                {"= F3"},
                {"= F4"},
                {"= F5"},
                {"= F6"},
                {"= F7"},
                {"= F8"},
                {"= F9"},
                {"= F10"},
                {"= F11"},
                {"= F12"},
                {"--------------------------"},
                {"= Left Ctrl"},
                {"= Left Shift"},
                {"= Left Alt"},
                {"= Left Win"},
                {"= Right Ctrl"},
                {"= Right Shift"},
                {"= Right Alt"},
                {"= Right Win"},
                {"--------------------------"},
                {"= Caps Lock"},
                {"= Backspace"},
                {"= Return"},
                {"= Insert"},
                {"= Delete"},
                {"= Tab"},
                {"--------------------------"},
                {"= Home"},
                {"= End"},
                {"= Page Up"},
                {"= Page Down"},
                {"--------------------------"},
                {"= Up Arrow"},
                {"= Down Arrow"},
                {"= Left Arrow"},
                {"= Right Arrow"},
                {"--------------------------"},
        };
//��ӽ�����岿�� ����ӽ�����ʾ�б���������������ʾ
M_SELECT serial_menu[] =
        {
                {"[ Serial ]"},
                {"- Function 0"},
                {"- Function 1"},
                {"- Function 2"},
                {"- Function 3"},
                {"- Function 4"},
                {"- Function 5"},
                {"- Function 6"},
                {"- Function 7"},
                {"- Function 8"},
        };

M_SELECT volt_menu[] =
        {
                {"EV"},
                {"EA"},
                {"A2"},
                {"A3"},
                {"A4"},
                {"A5"},
                {"A6"},
                {"A7"},
                {"B0"},
                {"B1"},
        };

M_SELECT setting_menu[] =
        {
                {"[ Setting ]"},
                {"~ Disp Bri"},
                {"~ Tile Ani"},
                {"~ List Ani"},
                {"~ Win Ani"},
                {"~ Spot Ani"},
                {"~ Tag Ani"},
                {"~ Fade Ani"},
                {"~ Btn SPT"},
                {"~ Btn LPT"},
                {"+ T Ufd Fm Scr"},
                {"+ L Ufd Fm Scr"},
                {"+ T Loop Mode"},
                {"+ L Loop Mode"},
                {"+ Win Bokeh Bg"},
                {"+ Knob Rot Dir"},
                {"+ Dark Mode"},
                {"- [ About ]"},
        };

M_SELECT about_menu[] =
        {
                {"[ WouoUI ]"},
                {"- Version: v2.1"},
                {"- Board: STM32H750"},
                {"- Ram: 1M"},
                {"- Flash: 128K"},
                {"- Freq: 480Mhz"},
                {"- Creator: Z1R343L"},
        };

/************************************* ͼƬ���� *************************************/
//��ӽ���ڶ����� ��ͼ��
const uint8_t main_icon_pic[][120] =
        {
                {//sleep
                        0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xF1,0x3F,
                        0xFF,0xFF,0xC3,0x3F,0xFF,0xFF,0x87,0x3F,0xFF,0xFF,0x07,0x3F,0xFF,0xFF,0x0F,0x3E,
                        0xFF,0xFF,0x0F,0x3E,0xFF,0xFF,0x0F,0x3C,0xFF,0xFF,0x0F,0x3C,0xFF,0xFF,0x0F,0x38,
                        0xFF,0xFF,0x0F,0x38,0xFF,0xFF,0x0F,0x38,0xFF,0xFF,0x07,0x38,0xFF,0xFF,0x07,0x38,
                        0xFF,0xFF,0x03,0x38,0xF7,0xFF,0x01,0x38,0xE7,0xFF,0x00,0x3C,0x87,0x3F,0x00,0x3C,
                        0x0F,0x00,0x00,0x3E,0x0F,0x00,0x00,0x3E,0x1F,0x00,0x00,0x3F,0x3F,0x00,0x80,0x3F,
                        0x7F,0x00,0xC0,0x3F,0xFF,0x01,0xF0,0x3F,0xFF,0x07,0xFC,0x3F,0xFF,0xFF,0xFF,0x3F,
                        0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0x3F
                },
                {//editor
                        0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0x3F,0xFF,0xF9,0xE7,0x3F,
                        0xFF,0xF9,0xE7,0x3F,0xFF,0xF9,0xE7,0x3F,0xFF,0xF0,0xE7,0x3F,0x7F,0xE0,0xE7,0x3F,
                        0x7F,0xE0,0xC3,0x3F,0x7F,0xE0,0xC3,0x3F,0x7F,0xE0,0xC3,0x3F,0x7F,0xE0,0xE7,0x3F,
                        0xFF,0xF0,0xE7,0x3F,0xFF,0xF9,0xE7,0x3F,0xFF,0xF9,0xE7,0x3F,0xFF,0xF9,0xE7,0x3F,
                        0xFF,0xF9,0xE7,0x3F,0xFF,0xF9,0xC3,0x3F,0xFF,0xF9,0x81,0x3F,0xFF,0xF0,0x81,0x3F,
                        0xFF,0xF0,0x81,0x3F,0xFF,0xF0,0x81,0x3F,0xFF,0xF9,0x81,0x3F,0xFF,0xF9,0xC3,0x3F,
                        0xFF,0xF9,0xE7,0x3F,0xFF,0xF9,0xE7,0x3F,0xFF,0xF9,0xE7,0x3F,0xFF,0xFF,0xFF,0x3F,
                        0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0x3F
                },
                {//volt
                        0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0x3F,0xEF,0xFF,0xFF,0x3F,0xC7,0xFF,0xFF,0x3F,
                        0xC7,0xF3,0xFF,0x3F,0x83,0xC0,0xFF,0x3F,0xEF,0xCC,0xFF,0x3F,0x6F,0x9E,0xFF,0x3F,
                        0x6F,0x9E,0xFF,0x3F,0x2F,0x3F,0xFF,0x3F,0x2F,0x3F,0xFF,0x3F,0x8F,0x7F,0xFE,0x3F,
                        0x8F,0x7F,0xFE,0x39,0x8F,0x7F,0xFE,0x39,0xCF,0xFF,0xFC,0x3C,0xCF,0xFF,0xFC,0x3C,
                        0xEF,0xFF,0xFC,0x3C,0xEF,0xFF,0x79,0x3E,0xEF,0xFF,0x79,0x3E,0xEF,0xFF,0x33,0x3F,
                        0xEF,0xFF,0x33,0x3F,0xEF,0xFF,0x87,0x3F,0xEF,0xFF,0xCF,0x3F,0xEF,0xFF,0x7F,0x3E,
                        0xEF,0xFF,0x7F,0x38,0x0F,0x00,0x00,0x30,0xFF,0xFF,0x7F,0x38,0xFF,0xFF,0x7F,0x3E,
                        0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0x3F,
                },
                {//Serial
                        0XFF,0X03,0XF0,0X3F,0XFF,0XFD,0XEF,0X3F,0XFF,0XFD,0XEF,0X3F,0XFF,0X0D,0XEC,0X3F,
                        0XFF,0X0D,0XEC,0X3F,0XFF,0X0D,0XEC,0X3F,0XFF,0XFD,0XEF,0X3F,0XFF,0XFD,0XEF,0X3F,
                        0X7F,0X00,0X80,0X3F,0X3F,0X00,0X00,0X3F,0X3F,0X00,0X00,0X3F,0X3F,0X00,0X00,0X3F,
                        0X3F,0XC0,0X00,0X3F,0X3F,0X80,0X0E,0X3F,0X3F,0X80,0X0E,0X3F,0X3F,0X98,0X06,0X3F,
                        0X3F,0X98,0X03,0X3F,0X3F,0X90,0X00,0X3F,0X3F,0XF0,0X00,0X3F,0X3F,0X80,0X00,0X3F,
                        0X3F,0XC0,0X00,0X3F,0X3F,0XC0,0X00,0X3F,0X7F,0X00,0X80,0X3F,0XFF,0X00,0XC0,0X3F,
                        0XFF,0X01,0XE0,0X3F,0XFF,0X03,0XF0,0X3F,0XFF,0X07,0XF8,0X3F,0XFF,0X0F,0XFC,0X3F,
                        0XFF,0X0F,0XFC,0X3F,0XFF,0X3F,0XFF,0X3F
                },
                {//settings
                        0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0x3F,
                        0xFF,0x1F,0xFE,0x3F,0xFF,0x1F,0xFE,0x3F,0xFF,0x0C,0xCC,0x3F,0x7F,0x00,0x80,0x3F,
                        0x3F,0x00,0x00,0x3F,0x3F,0xE0,0x01,0x3F,0x7F,0xF8,0x87,0x3F,0x7F,0xFC,0x8F,0x3F,
                        0x3F,0xFC,0x0F,0x3F,0x0F,0x3E,0x1F,0x3C,0x0F,0x1E,0x1E,0x3C,0x0F,0x1E,0x1E,0x3C,
                        0x0F,0x3E,0x1F,0x3C,0x3F,0xFC,0x0F,0x3F,0x7F,0xFC,0x8F,0x3F,0x7F,0xF8,0x87,0x3F,
                        0x3F,0xE0,0x01,0x3F,0x3F,0x00,0x00,0x3F,0x7F,0x00,0x80,0x3F,0xFF,0x0C,0xCC,0x3F,
                        0xFF,0x1F,0xFE,0x3F,0xFF,0x1F,0xFE,0x3F,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0x3F,
                        0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0x3F
                },
        };


//stdlib����
char *myitoa(uint32_t num)
{
    static char str[10] = {0};
    memset(str, 0, sizeof(str));
    sprintf(str, "%d", num);
    return str;
}
char *ftoa(float num)
{
    static char str[10] = {0};
    memset(str, 0, sizeof(str));
    sprintf(str, "%.2f", num);
    return str;
}

/************************************ ��ʼ������ ***********************************/

/********************************* ��ʼ�����ݴ����� *******************************/

// ��ʾ��ֵ�ĳ�ʼ��
void check_box_v_init(uint8_t *param)
{
    check_box.v = param;
}

// ��ѡ��ĳ�ʼ��
void check_box_m_init(uint8_t *param)
{
    check_box.m = param;
}

// ��ѡ��ʱ�ĳ�ʼ��
void check_box_s_init(uint8_t *param, uint8_t *param_p)
{
    check_box.s = param;
    check_box.s_p = param_p;
}

// ��ѡ������
void check_box_m_select(uint8_t param)
{
    check_box.m[param] = !check_box.m[param];
}

// ��ѡ������
void check_box_s_select(uint8_t val, uint8_t pos)
{
    *check_box.s = val;
    *check_box.s_p = pos;
}

// ������ֵ��ʼ��
void window_value_init(char title[], uint8_t select, uint8_t *value, uint8_t max, uint8_t min, uint8_t step, M_SELECT *bg, uint8_t index)
{
    strcpy(win.title, title);
    win.select = select;
    win.value = value;
    win.max = max;
    win.min = min;
    win.step = step;
    win.bg = bg;
    win.index = index;
    ui.index = M_WINDOW;
    ui.state = S_WINDOW;
}

// ȷ�ϵ�����ֵ��ʼ��
void confirm_window_value_init(char title[], uint8_t _select_btn, fun_callback_t _cb, M_SELECT *bg, uint8_t index)
{
    strcpy(con_win.title, title);
    con_win.cb = _cb;
    con_win.select_btn = _select_btn;
    con_win.bg = bg;
    con_win.index = index;
    ui.index = M_CONFIRM_WINDOW;
    ui.state = S_CONFIRM_WINDOW;
}

// ȷ�ϵ�����ֵ��ʼ��
void confirm_window_select_button(uint8_t btn)
{
    if(btn)
    {
        con_win.btn_x_trg = con_win.l;
    }
    else
    {
        con_win.btn_x_trg = con_win.l + 78;
    }
}

/********************************* ��ҳ���ʼ������ ********************************/

// ���������ʱ�ĳ�ʼ��
void tile_param_init(void)
{
    ui.init = false;
    tile.icon_x = 0;
    tile.icon_x_trg = TILE_ICON_S;
    tile.icon_y = -TILE_ICON_H;
    tile.icon_y_trg = 0;
    tile.indi_x = 0;
    tile.indi_x_trg = TILE_INDI_W;
    tile.title_y = tile.title_y_calc;
    tile.title_y_trg = tile.title_y_trg_calc;
}

// ����˯��ʱ�ĳ�ʼ��
void sleep_param_init(void)
{
    u8g2_SetDrawColor(&u8g2, 0);
    u8g2_DrawBox(&u8g2, 0, 0, DISP_W, DISP_H);
    u8g2_SetPowerSave(&u8g2, 1);
    ui.state = S_NONE;
    ui.sleep = true;
}

// ��ť����ҳ��ʼ��
void knob_param_init(void)
{
    check_box_v_init(knob.param);
}

// ��ť��תҳ��ʼ��
void krf_param_init(void)
{
    check_box_s_init(&knob.param[KNOB_ROT], &knob.param[KNOB_ROT_P]);
}

// ��ť�㰴ҳ��ʼ��
void kpf_param_init(void)
{
    check_box_s_init(&knob.param[KNOB_COD], &knob.param[KNOB_COD_P]);
}

// ��ѹ����ҳ��ʼ��
void volt_param_init(void)
{
    volt.text_bg_r = 0;
    volt.text_bg_r_trg = VOLT_TEXT_BG_W;
}

// ����ҳ��ʼ��
void setting_param_init(void)
{
    check_box_v_init(ui.param);
    check_box_m_init(ui.param);
}

/********************************** ͨ�ó�ʼ������ *********************************/

/*
  ҳ��㼶�����߼��ǣ�������ҳ�涼�ȵ����б����ʼ���������б��ఴ�����ٳ�ʼ����Ӧ����
  ���������˷�һЩ��Դ������תҳ��ʱֻ��Ҫ����ҳ��㼶���߼��ϸ����������ٳ���
*/

// ����������ʼ��
void window_param_init(void)
{
    win.bar = 0;
    win.y = WIN_Y;
    win.y_trg = win.u;
    ui.state = S_NONE;
}

void confirm_windos_param_init(void)
{
    con_win.y = CON_WIN_Y;
    con_win.y_trg = con_win.u;
    confirm_window_select_button(con_win.select_btn);
    ui.state = S_NONE;
}

// �������㼶ʱ�ĳ�ʼ��
void layer_init_in(void)
{
    ui.layer++;
    ui.init = 0;
    list.y = 0;
    list.y_trg = LIST_LINE_H;
    list.box_x = 0;
    list.box_y = 0;
    list.bar_y = 0;
    ui.state = S_FADE;
    switch (ui.index)
    {
        case M_MAIN:
            tile_param_init();
            break; // ˯�߽������˵���������ʼ��
        case M_KNOB:
            knob_param_init();
            break; // ��ť����ҳ����ĩβ���ֳ�ʼ��
        case M_KRF:
            krf_param_init();
            break; // ��ť��תҳ����ѡ���ʼ��
        case M_KPF:
            kpf_param_init();
            break; // ��ť�㰴ҳ����ѡ���ʼ��
        case M_VOLT:
            volt_param_init();
            break; // ���˵������ѹ����ҳ��������ʼ��
        case M_SETTING:
            setting_param_init();
            break; // ���˵���������ҳ����ѡ���ʼ��
    }
}

// �����ǳ�㼶ʱ�ĳ�ʼ��
void layer_init_out(void)
{
    ui.select[ui.layer] = 0;
    list.box_y_trg[ui.layer] = 0;
    ui.layer--;
    ui.init = 0;
    list.y = 0;
    list.y_trg = LIST_LINE_H;
    list.bar_y = 0;
    ui.state = S_FADE;
    switch (ui.index)
    {
        case M_SLEEP:
            sleep_param_init();
            break; // ���˵�����˯��ҳ������Ƿ���ҪдEEPROM
        case M_MAIN:
            tile_param_init();
            break; // ����ʲôҳ��������˵�ʱ��������ʼ��
    }
}

/************************************* �������� *************************************/

// ��������
void animation(float *a, float *a_trg, uint8_t n)
{
    if (*a != *a_trg)
    {
        if (fabs(*a - *a_trg) < 0.15) *a = *a_trg;
        else *a += (*a_trg - *a) / (ui.param[n] / 10.0);
    }
}

// ��ʧ����
void fade(void)
{
    HAL_Delay(ui.param[FADE_ANI]);
    if (ui.param[DARK_MODE])
    {
        switch (ui.fade)
        {
            case 1:
                for (uint16_t i = 0; i < buf_len; ++i)
                    if (i % 2 != 0)
                        buf_ptr[i] = buf_ptr[i] & 0xAA;
                break;
            case 2:
                for (uint16_t i = 0; i < buf_len; ++i)
                    if (i % 2 != 0)
                        buf_ptr[i] = buf_ptr[i] & 0x00;
                break;
            case 3:
                for (uint16_t i = 0; i < buf_len; ++i)
                    if (i % 2 == 0)
                        buf_ptr[i] = buf_ptr[i] & 0x55;
                break;
            case 4:
                for (uint16_t i = 0; i < buf_len; ++i)
                    if (i % 2 == 0)
                        buf_ptr[i] = buf_ptr[i] & 0x00;
                break;
            default:
                ui.state = S_NONE;
                ui.fade = 0;
                break;
        }
    }
    else
    {
        switch (ui.fade)
        {
            case 1:
                for (uint16_t i = 0; i < buf_len; ++i)
                    if (i % 2 != 0)
                        buf_ptr[i] = buf_ptr[i] | 0xAA;
                break;
            case 2:
                for (uint16_t i = 0; i < buf_len; ++i)
                    if (i % 2 != 0)
                        buf_ptr[i] = buf_ptr[i] | 0x00;
                break;
            case 3:
                for (uint16_t i = 0; i < buf_len; ++i)
                    if (i % 2 == 0)
                        buf_ptr[i] = buf_ptr[i] | 0x55;
                break;
            case 4:
                for (uint16_t i = 0; i < buf_len; ++i)
                    if (i % 2 == 0)
                        buf_ptr[i] = buf_ptr[i] | 0x00;
                break;
            default:
                ui.state = S_NONE;
                ui.fade = 0;
                break;
        }
    }
    ui.fade++;
}

/************************************* ��ʾ���� *************************************/

// ������ҳ��ͨ����ʾ����
void tile_show(struct MENU arr_1[], const uint8_t icon_pic[][120])
{
    // ���㶯������ֵ
    animation(&tile.icon_x, &tile.icon_x_trg, TILE_ANI);
    animation(&tile.icon_y, &tile.icon_y_trg, TILE_ANI);
    animation(&tile.indi_x, &tile.indi_x_trg, TILE_ANI);
    animation(&tile.title_y, &tile.title_y_trg, TILE_ANI);

    // ���ô�������ɫ��0͸�ԣ�1ʵ�ԣ�2��ɫ��������ʵ��
    u8g2_SetDrawColor(&u8g2, 1);

    // ���ƴ����
    u8g2_SetFont(&u8g2, TILE_B_FONT);
    u8g2_DrawStr(&u8g2, ((DISP_W - TILE_INDI_W) - u8g2_GetStrWidth(&u8g2, arr_1[ui.select[ui.layer]].m_select)) / 2 + TILE_INDI_W, tile.title_y, arr_1[ui.select[ui.layer]].m_select);

    //���ƴ����ָʾ��
    u8g2_DrawBox(&u8g2, 0, TILE_ICON_S, tile.indi_x, TILE_INDI_H);

    //����ͼ��
    if (!ui.init)
    {
        for (uint8_t i = 0; i < ui.num[ui.index]; ++i)
        {
            if (ui.param[TILE_UFD])
                tile.temp = (DISP_W - TILE_ICON_W) / 2 + i * tile.icon_x - TILE_ICON_S * ui.select[ui.layer];
            else
                tile.temp = (DISP_W - TILE_ICON_W) / 2 + (i - ui.select[ui.layer]) * tile.icon_x;
            u8g2_DrawXBMP(&u8g2, tile.temp, (int16_t)tile.icon_y, TILE_ICON_W, TILE_ICON_H, icon_pic[i]);
        }
        if (tile.icon_x == tile.icon_x_trg)
        {
            ui.init = true;
            tile.icon_x = tile.icon_x_trg = -ui.select[ui.layer] * TILE_ICON_S;
        }
    }
    else for (uint8_t i = 0; i < ui.num[ui.index]; ++i) u8g2_DrawXBMP(&u8g2, (DISP_W - TILE_ICON_W) / 2 + (int16_t)tile.icon_x + i * TILE_ICON_S, 0, TILE_ICON_W, TILE_ICON_H, icon_pic[i]);

    //��ת��Ļ��Ԫ����ɫ������ģʽ����
    u8g2_SetDrawColor(&u8g2, 2);
    if (!ui.param[DARK_MODE])
    {
        u8g2_DrawBox(&u8g2, 0, 0, DISP_W, DISP_H);
    }
}

/*************** �����б�ÿ�п�ͷ���ţ��ж�ÿ��β���Ƿ�����Լ�����ʲô���� *************/

// �б���ʾ��ֵ
void list_draw_value(int x, int y, int n) { u8g2_DrawStr(&u8g2, x, y, myitoa(check_box.v[n - 1])); }

// �������
void list_draw_check_box_frame(void) { u8g2_DrawRFrame(&u8g2, CHECK_BOX_L_S, list.temp + CHECK_BOX_U_S, CHECK_BOX_F_W, CHECK_BOX_F_H, 1); }

// ���ƿ�����ĵ�
void list_draw_check_box_dot(void) { u8g2_DrawBox(&u8g2, CHECK_BOX_L_S + CHECK_BOX_D_S + 1, list.temp + CHECK_BOX_U_S + CHECK_BOX_D_S + 1, CHECK_BOX_F_W - (CHECK_BOX_D_S + 1) * 2, CHECK_BOX_F_H - (CHECK_BOX_D_S + 1) * 2); }

// �б���ʾ��ť����
void list_draw_krf(int x, int y, int n)
{
    switch (check_box.v[n - 1])
    {
        case 0:
            u8g2_DrawStr(&u8g2, x, y, "OFF");
            break;
        case 1:
            u8g2_DrawStr(&u8g2, x, y, "VOL");
            break;
        case 2:
            u8g2_DrawStr(&u8g2, x, y, "BRI");
            break;
    }
}

// �б���ʾ������ֵ
void list_draw_kpf(int x, int y, int n)
{
    if (check_box.v[n - 1] == 0)
        u8g2_DrawStr(&u8g2, x, y, "OFF");
    else if (check_box.v[n - 1] <= 90)
        u8g2_DrawStr(&u8g2, x, y, myitoa((char)check_box.v[n - 1]));
    else
        u8g2_DrawStr(&u8g2, x, y, "?");
}

// �ж��б�β������
void list_draw_text_and_check_box(struct MENU arr[], int i)
{
    u8g2_DrawStr(&u8g2, LIST_TEXT_S, list.temp + LIST_TEXT_H + LIST_TEXT_S, arr[i].m_select);
    switch (arr[i].m_select[0])
    {
        case '~':
            list_draw_value(CHECK_BOX_L_S, list.temp + LIST_TEXT_H + LIST_TEXT_S, i);
            break;
        case '+':
            list_draw_check_box_frame();
            if (check_box.m[i - 1] == 1)
                list_draw_check_box_dot();
            break;
        case '=':
            list_draw_check_box_frame();
            if (*check_box.s_p == i)
                list_draw_check_box_dot();
            break;
        case '#':
            list_draw_krf(CHECK_BOX_L_S, list.temp + LIST_TEXT_H + LIST_TEXT_S, i);
            break;
        case '$':
            list_draw_kpf(CHECK_BOX_L_S, list.temp + LIST_TEXT_H + LIST_TEXT_S, i);
            break;
    }
}

/******************************** �б���ʾ���� **************************************/
// �б���ҳ��ͨ����ʾ����
void list_show(struct MENU arr[], uint8_t ui_index)
{
    // ���¶���Ŀ��ֵ
    u8g2_SetFont(&u8g2, LIST_FONT);
    list.box_x_trg = u8g2_GetStrWidth(&u8g2, arr[ui.select[ui.layer]].m_select) + LIST_TEXT_S * 2;
    list.bar_y_trg = ceil((ui.select[ui.layer]) * ((float)DISP_H / (ui.num[ui_index] - 1)));

    //���㶯������ֵ
    animation(&list.y, &list.y_trg, LIST_ANI);
    animation(&list.box_x, &list.box_x_trg, LIST_ANI);
    animation(&list.box_y, &list.box_y_trg[ui.layer], LIST_ANI);
    animation(&list.bar_y, &list.bar_y_trg, LIST_ANI);

    //���ѭ�������Ƿ����
    if (list.loop && list.box_y == list.box_y_trg[ui.layer])
        list.loop = false;

    //�������ֺͽ�������ɫ��0͸�ԣ�1ʵ�ԣ�2��ɫ�����ﶼ��ʵ��
    u8g2_SetDrawColor(&u8g2, 1);

    //���ƽ�����
    u8g2_DrawHLine(&u8g2, DISP_W - LIST_BAR_W, 0, LIST_BAR_W);
    u8g2_DrawHLine(&u8g2, DISP_W - LIST_BAR_W, DISP_H - 1, LIST_BAR_W);
    u8g2_DrawVLine(&u8g2, DISP_W - ceil((float)LIST_BAR_W / 2), 0, DISP_H);
    u8g2_DrawBox(&u8g2, DISP_W - LIST_BAR_W, 0, LIST_BAR_W, list.bar_y);

    //�����б�����
    if (!ui.init)
    {
        for (int i = 0; i < ui.num[ui_index]; ++i)
        {
            if (ui.param[LIST_UFD])
                list.temp = i * list.y - LIST_LINE_H * ui.select[ui.layer] + list.box_y_trg[ui.layer];
            else
                list.temp = (i - ui.select[ui.layer]) * list.y + list.box_y_trg[ui.layer];
            list_draw_text_and_check_box(arr, i);
        }
        if (list.y == list.y_trg)
        {
            ui.init = true;
            list.y = list.y_trg = -LIST_LINE_H * ui.select[ui.layer] + list.box_y_trg[ui.layer];
        }
    }
    else for (int i = 0; i < ui.num[ui_index]; ++ i)
        {
            list.temp = LIST_LINE_H * i + list.y;
            list_draw_text_and_check_box(arr, i);
        }

    //��������ѡ���0͸�ԣ�1ʵ�ԣ�2��ɫ�������÷�ɫ
    u8g2_SetDrawColor(&u8g2, 2);
    u8g2_DrawRBox(&u8g2, 0, list.box_y, list.box_x, LIST_LINE_H, (u8g2_uint_t)LIST_BOX_R);

    //��ת��Ļ��Ԫ����ɫ������ģʽ���֣��������������б�����ҳ�棬ʹ�����������Ǹ�ҳ����
    if (!ui.param[DARK_MODE])
    {
        u8g2_DrawBox(&u8g2, 0, 0, DISP_W, DISP_H);
        switch (ui.index)
        {
            case M_WINDOW:
            case M_CONFIRM_WINDOW:
            case M_VOLT:
                u8g2_DrawBox(&u8g2, 0, 0, DISP_W, DISP_H);
        }
    }
}

// ��ѹҳ����ʾ����
void volt_show(void)
{
    // ʹ���б�����ʾѡ��
    list_show(volt_menu, M_VOLT);

    // ���㶯������ֵ
    animation(&volt.text_bg_r, &volt.text_bg_r_trg, TAG_ANI);

    // ����������ɫ��0͸�ԣ�1ʵ�ԣ�2��ɫ��������ʵ��
    u8g2_SetDrawColor(&u8g2, 1);

    // ���Ƶ�ѹ���ߺ����
    volt.val = 0;
    u8g2_DrawFrame(&u8g2, WAVE_BOX_L_S, 0, WAVE_BOX_W, WAVE_BOX_H);
    u8g2_DrawFrame(&u8g2, WAVE_BOX_L_S + 1, 1, WAVE_BOX_W - 2, WAVE_BOX_H - 2);
    if (list.box_y == list.box_y_trg[ui.layer] && list.y == list.y_trg)
    {
        memcpy(volt.ch0_adc, volt.ch0_adc + 1, WAVE_W-2);
//        volt.ch0_adc[WAVE_W - 1] = power_monitor_read_value(ui.select[ui.layer]);
        for (int i = 1; i < WAVE_W - 1; i++)
        {
//            volt.val += power_monitor_read_value(ui.select[ui.layer]);
//            volt.ch0_wave[i] = map_number(power_monitor_read_value(ui.select[ui.layer]), 0, 4095, WAVE_MAX, WAVE_MIN);
            u8g2_DrawLine(&u8g2, WAVE_L + i - 1, WAVE_U + volt.ch0_wave[i - 1], WAVE_L + i, WAVE_U + volt.ch0_wave[i]);
        }
    }

    // ���Ƶ�ѹֵ
    u8g2_SetFontDirection(&u8g2, 0);
    u8g2_SetFont(&u8g2, VOLT_FONT);
    if(ui.select[ui.layer] == 0)
    {
        volt.val = volt.val / WAVE_W;
        u8g2_DrawStr(&u8g2, 39, DISP_H - 6, ftoa(volt.val / 4096.0 * 13.8));
        u8g2_DrawStr(&u8g2, DISP_W-28, DISP_H - 6, "V");
    }
    else if((ui.select[ui.layer] == 1))
    {
        volt.val = volt.val / WAVE_W;
//        volt.val = ((volt.val / 4096.0 * 3.3)-1.648)/(AMPS_RATIO);
        u8g2_DrawStr(&u8g2, 39, DISP_H - 6, ftoa(volt.val));
        u8g2_DrawStr(&u8g2, DISP_W-28, DISP_H - 6, "A");
    }

    // �����б�ѡ���͵�ѹ���ֱ���
    u8g2_SetDrawColor(&u8g2, 2);
    u8g2_DrawBox(&u8g2, VOLT_TEXT_BG_L_S, DISP_H - VOLT_TEXT_BG_H, volt.text_bg_r, VOLT_TEXT_BG_H);

    // ��ת��Ļ��Ԫ����ɫ������ģʽ����
    if (!ui.param[DARK_MODE])
        u8g2_DrawBox(&u8g2, 0, 0, DISP_W, DISP_H);
}

// ����ͨ����ʾ����
void window_show(void)
{
    // ���Ʊ����б����ݿ����жϱ����Ƿ�Ҫ�黯
    list_show(win.bg, win.index);
    if (ui.param[WIN_BOK])
        for (uint16_t i = 0; i < buf_len; ++i)
            buf_ptr[i] = buf_ptr[i] & (i % 2 == 0 ? 0x55 : 0xAA);

    // ���¶���Ŀ��ֵ
    u8g2_SetFont(&u8g2, WIN_FONT);
    win.bar_trg = (float)(*win.value - win.min) / (float)(win.max - win.min) * (WIN_BAR_W - 4);

    // ���㶯������ֵ
    animation(&win.bar, &win.bar_trg, WIN_ANI);
    animation(&win.y, &win.y_trg, WIN_ANI);

    // ���ƴ���
    u8g2_SetDrawColor(&u8g2, 0);
    u8g2_DrawRBox(&u8g2, win.l, (int16_t)win.y, WIN_W, WIN_H, 2); // ������򱳾�
    u8g2_SetDrawColor(&u8g2, 1);
    u8g2_DrawRFrame(&u8g2, win.l, (int16_t)win.y, WIN_W, WIN_H, 2);                  // ����������
    u8g2_DrawRFrame(&u8g2, win.l + 5, (int16_t)win.y + 20, WIN_BAR_W, WIN_BAR_H, 1); // ���ƽ��������
    u8g2_DrawBox(&u8g2, win.l + 7, (int16_t)win.y + 22, win.bar, WIN_BAR_H - 4);     // ���ƽ�����
    u8g2_DrawStr(&u8g2, win.l + 5, (int16_t)win.y + 14, win.title); // ���Ʊ���
    u8g2_DrawStr(&u8g2, win.l + 78, (int16_t)win.y + 14, myitoa(*win.value)); // ���Ƶ�ǰֵ

    // ��Ҫ�ڴ����޸Ĳ���ʱ������Ч�ĺ���
    if (!strcmp(win.title, "Disp Bri"))//Ĭ��Ƶ��������Ч
        u8g2_SetContrast(&u8g2, ui.param[DISP_BRI]);

    // ��ת��Ļ��Ԫ����ɫ������ģʽ����
    u8g2_SetDrawColor(&u8g2, 2);
    if (!ui.param[DARK_MODE])
        u8g2_DrawBox(&u8g2, 0, 0, DISP_W, DISP_H);
}

// ȷ�ϵ���ͨ����ʾ����
void confirm_window_show(void)
{
    // ���Ʊ����б����ݿ����жϱ����Ƿ�Ҫ�黯
    list_show(con_win.bg, con_win.index);
    if (ui.param[WIN_BOK])
        for (uint16_t i = 0; i < buf_len; ++i)
            buf_ptr[i] = buf_ptr[i] & (i % 2 == 0 ? 0x55 : 0xAA);

    // ���㶯������ֵ
    animation(&con_win.y, &con_win.y_trg, WIN_ANI);
    animation(&con_win.btn_x, &con_win.btn_x_trg, WIN_ANI);

    // ���ƴ���
    u8g2_SetDrawColor(&u8g2, 0);
    u8g2_DrawRBox(&u8g2, con_win.l, (int16_t)con_win.y, CON_WIN_W, CON_WIN_H, 2); 	// ������򱳾�
    u8g2_SetDrawColor(&u8g2, 1);
    u8g2_DrawRFrame(&u8g2, con_win.l, (int16_t)con_win.y, CON_WIN_W, CON_WIN_H, 2);	// ����������
    u8g2_DrawStr(&u8g2, con_win.l + 40, (int16_t)con_win.y + 14, con_win.title); 		// ���Ʊ���
    u8g2_DrawStr(&u8g2, con_win.l + 5, (int16_t)con_win.y + 28, "YES"); 						// ����YES
    u8g2_DrawStr(&u8g2, DISP_W - con_win.l - 20, (int16_t)con_win.y + 28, "NO"); 		// ����NO
    u8g2_SetDrawColor(&u8g2, 2);
    if(con_win.select_btn)
        u8g2_DrawRBox(&u8g2, con_win.btn_x + 4, (int16_t)con_win.y + 15, 21, LIST_LINE_H, (u8g2_uint_t)LIST_BOX_R); 	// ������򱳾�
    else
        u8g2_DrawRBox(&u8g2, con_win.btn_x + 4, (int16_t)con_win.y + 15, 15, LIST_LINE_H, (u8g2_uint_t)LIST_BOX_R); 	// ������򱳾�

    // ��ת��Ļ��Ԫ����ɫ������ģʽ����
    u8g2_SetDrawColor(&u8g2, 2);
    if (!ui.param[DARK_MODE])
        u8g2_DrawBox(&u8g2, 0, 0, DISP_W, DISP_H);
}

/************************************* ������ *************************************/

/*********************************** ͨ�ô����� ***********************************/
/**
  * @brief  tile_rotate_switch
  * @note   ������ҳ����תʱ�ж�ͨ�ú���
  * @param  CC ��һ�� CW ��һ��
  * @retval None
  */
void tile_rotate_switch(void)
{
    switch (btn.id)
    {
        case BTN_ID_CC:
            if (ui.init)
            {
                if (ui.select[ui.layer] > 0)
                {
                    ui.select[ui.layer] -= 1;
                    tile.icon_x_trg += TILE_ICON_S;
                    tile.select_flag = false;
                }
                else
                {
                    if (ui.param[TILE_LOOP])
                    {
                        ui.select[ui.layer] = ui.num[ui.index] - 1;
                        tile.icon_x_trg = -TILE_ICON_S * (ui.num[ui.index] - 1);
                        break;
                    }
                    else
                        tile.select_flag = true;
                }
            }
            break;

        case BTN_ID_CW:
            if (ui.init)
            {
                if (ui.select[ui.layer] < (ui.num[ui.index] - 1))
                {
                    ui.select[ui.layer] += 1;
                    tile.icon_x_trg -= TILE_ICON_S;
                    tile.select_flag = false;
                }
                else
                {
                    if (ui.param[TILE_LOOP])
                    {
                        ui.select[ui.layer] = 0;
                        tile.icon_x_trg = 0;
                        break;
                    }
                    else
                        tile.select_flag = true;
                }
            }
            break;
    }
}
// �б���ҳ����תʱ�ж�ͨ�ú���
void list_rotate_switch(void)
{
    if (!list.loop)
    {
        switch (btn.id)
        {
            case BTN_ID_CC:
                if (ui.select[ui.layer] == 0)
                {
                    if (ui.param[LIST_LOOP] && ui.init)
                    {
                        list.loop = true;
                        ui.select[ui.layer] = ui.num[ui.index] - 1;
                        if (ui.num[ui.index] > list.line_n)
                        {
                            list.box_y_trg[ui.layer] = DISP_H - LIST_LINE_H;
                            list.y_trg = DISP_H - ui.num[ui.index] * LIST_LINE_H;
                        }
                        else
                            list.box_y_trg[ui.layer] = (ui.num[ui.index] - 1) * LIST_LINE_H;
                        break;
                    }
                    else
                        break;
                }
                if (ui.init)
                {
                    ui.select[ui.layer] -= 1;
                    if (ui.select[ui.layer] < -(list.y_trg / LIST_LINE_H))
                    {
                        if (!(DISP_H % LIST_LINE_H))
                            list.y_trg += LIST_LINE_H;
                        else
                        {
                            if (list.box_y_trg[ui.layer] == DISP_H - LIST_LINE_H * list.line_n)
                            {
                                list.y_trg += (list.line_n + 1) * LIST_LINE_H - DISP_H;
                                list.box_y_trg[ui.layer] = 0;
                            }
                            else if (list.box_y_trg[ui.layer] == LIST_LINE_H)
                            {
                                list.box_y_trg[ui.layer] = 0;
                            }
                            else
                                list.y_trg += LIST_LINE_H;
                        }
                    }
                    else
                        list.box_y_trg[ui.layer] -= LIST_LINE_H;
                    break;
                }

            case BTN_ID_CW:
                if (ui.select[ui.layer] == (ui.num[ui.index] - 1))
                {
                    if (ui.param[LIST_LOOP] && ui.init)
                    {
                        list.loop = true;
                        ui.select[ui.layer] = 0;
                        list.y_trg = 0;
                        list.box_y_trg[ui.layer] = 0;
                        break;
                    }
                    else
                        break;
                }
                if (ui.init)
                {
                    ui.select[ui.layer] += 1;
                    if ((ui.select[ui.layer] + 1) > (list.line_n - list.y_trg / LIST_LINE_H))
                    {
                        if (!(DISP_H % LIST_LINE_H))
                            list.y_trg -= LIST_LINE_H;
                        else
                        {
                            if (list.box_y_trg[ui.layer] == LIST_LINE_H * (list.line_n - 1))
                            {
                                list.y_trg -= (list.line_n + 1) * LIST_LINE_H - DISP_H;
                                list.box_y_trg[ui.layer] = DISP_H - LIST_LINE_H;
                            }
                            else if (list.box_y_trg[ui.layer] == DISP_H - LIST_LINE_H * 2)
                            {
                                list.box_y_trg[ui.layer] = DISP_H - LIST_LINE_H;
                            }
                            else
                                list.y_trg -= LIST_LINE_H;
                        }
                    }
                    else
                        list.box_y_trg[ui.layer] += LIST_LINE_H;
                    break;
                }
                break;
        }
    }
}

// ����ͨ�ô�����
void window_proc(void)
{
    window_show();
    if (win.y == WIN_Y_TRG)
        ui.index = win.index;
    if (btn.pressed && win.y == win.y_trg && win.y != WIN_Y_TRG)
    {
        btn.pressed = false;
        switch (btn.id)
        {
            case BTN_ID_CW:
                if (*win.value < win.max)
                    *win.value += win.step;
                eeprom_notify_change();
                break;
            case BTN_ID_CC:
                if (*win.value > win.min)
                    *win.value -= win.step;
                eeprom_notify_change();
                break;
            case BTN_ID_SP:
            case BTN_ID_LP:
                win.y_trg = WIN_Y_TRG;
                break;
        }
    }
}
// ����ͨ�ô�����
void confirm_window_proc(void)
{
    confirm_window_show();
    if (con_win.y == CON_WIN_Y_TRG)
        ui.index = con_win.index;
    if (btn.pressed && con_win.y == con_win.y_trg && con_win.y != CON_WIN_Y_TRG)
    {
        btn.pressed = false;
        switch (btn.id)
        {
            case BTN_ID_CW:
                con_win.select_btn = 0;
                confirm_window_select_button(con_win.select_btn);
                eeprom_notify_change();
                break;
            case BTN_ID_CC:
                con_win.select_btn = 1;
                confirm_window_select_button(con_win.select_btn);
                eeprom_notify_change();
                break;
            case BTN_ID_SP:
            case BTN_ID_LP:
                con_win.cb(con_win.select_btn);
                con_win.y_trg = CON_WIN_Y_TRG;
                break;
        }
    }
}

/********************************** ��ҳ�洦���� **********************************/

// ˯��ҳ�洦����
void sleep_proc(void)
{
    while (ui.sleep)
    {
        // ˯��ʱѭ��ִ�еĺ���
        // ˯��ʱ��Ҫɨ����ť�����˳�˯��
        // ����ť�ж���ʱ
        if (btn.pressed)
        {
            btn.pressed = false;
            switch (btn.id)
            {
                case BTN_ID_CW:// ˯��ʱ˳ʱ����תִ�еĺ���
                    switch (knob.param[KNOB_ROT])
                    {
                        case KNOB_ROT_VOL:
                            break;
                        case KNOB_ROT_BRI:
                            break;
                    }
                    break;
                case BTN_ID_CC:// ˯��ʱ��ʱ����תִ�еĺ���
                    switch (knob.param[KNOB_ROT])
                    {
                        case KNOB_ROT_VOL:
                            break;
                        case KNOB_ROT_BRI:
                            break;
                    }
                    break;
                case BTN_ID_SP:// ˯��ʱ�̰�ִ�еĺ���
                    break;
                case BTN_ID_LP:// ˯��ʱ����ִ�еĺ���
                    ui.index = M_MAIN;
                    ui.state = S_LAYER_IN;
                    u8g2_SetPowerSave(&u8g2, 0);
                    ui.sleep = false;
                    break;
            }
        }
    }
}

// ���˵���������������ģ��
// �˽�����Ӳ˵��ͬʱenumҲҪ����
void main_proc(void)
{
    tile_show(main_menu, main_icon_pic);
    if (btn.pressed)
    {
        btn.pressed = false;
        switch (btn.id)
        {
            case BTN_ID_CW:
            case BTN_ID_CC:
                tile_rotate_switch();
                break;
            case BTN_ID_SP://��ӽ���������� �ӿ��ƽ��� ͬʱ��menu.h�������״̬ö��
                switch (ui.select[ui.layer])
                {
                    case 0:
                        ui.index = M_SLEEP;
                        ui.state = S_LAYER_OUT;
                        break;
                    case 1:
                        ui.index = M_EDITOR;
                        ui.state = S_LAYER_IN;
                        break;
                    case 2:
                        ui.index = M_VOLT;
                        ui.state = S_LAYER_IN;
                        break;
                    case 3:
                        ui.index = M_SERIAL;
                        ui.state = S_LAYER_IN;
                        break;
                    case 4:
                        ui.index = M_SETTING;
                        ui.state = S_LAYER_IN;
                        break;
                }
        }
        if (!tile.select_flag && ui.init)
        {
            tile.indi_x = 0;
            tile.title_y = tile.title_y_calc;
        }
    }
}

// �༭���˵�������
void editor_proc(void)
{
    list_show(editor_menu, M_EDITOR);
    if (btn.pressed)
    {
        btn.pressed = false;
        switch (btn.id)
        {
            case BTN_ID_CW:
            case BTN_ID_CC:
                list_rotate_switch();
                break;
            case BTN_ID_LP:
                ui.select[ui.layer] = 0;
            case BTN_ID_SP:
                switch (ui.select[ui.layer])
                {
                    case 0:
                        ui.index = M_MAIN;
                        ui.state = S_LAYER_OUT;
                        break;
                    case 11:
                        ui.index = M_KNOB;
                        ui.state = S_LAYER_IN;
                        break;
                }
        }
    }
}

// ��ť�༭�˵�������
void knob_proc(void)
{
    list_show(knob_menu, M_KNOB);
    if (btn.pressed)
    {
        btn.pressed = false;
        switch (btn.id)
        {
            case BTN_ID_CW:
            case BTN_ID_CC:
                list_rotate_switch();
                break;
            case BTN_ID_LP:
                ui.select[ui.layer] = 0;
            case BTN_ID_SP:
                switch (ui.select[ui.layer])
                {
                    case 0:
                        ui.index = M_EDITOR;
                        ui.state = S_LAYER_OUT;
                        break;
                    case 1:
                        ui.index = M_KRF;
                        ui.state = S_LAYER_IN;
                        check_box_s_init(&knob.param[KNOB_ROT], &knob.param[KNOB_ROT_P]);
                        break;
                    case 2:
                        ui.index = M_KPF;
                        ui.state = S_LAYER_IN;
                        check_box_s_init(&knob.param[KNOB_COD], &knob.param[KNOB_COD_P]);
                        break;
                }
        }
    }
}

// ��ť��ת���ܲ˵�������
void krf_proc(void)
{
    list_show(krf_menu, M_KRF);
    if (btn.pressed)
    {
        btn.pressed = false;
        switch (btn.id)
        {
            case BTN_ID_CW:
            case BTN_ID_CC:
                list_rotate_switch();
                break;
            case BTN_ID_LP:
                ui.select[ui.layer] = 0;
            case BTN_ID_SP:
                switch (ui.select[ui.layer])
                {
                    case 0:
                        ui.index = M_KNOB;
                        ui.state = S_LAYER_OUT;
                        break;
                    case 1:
                        break;
                    case 2:
                        check_box_s_select(KNOB_DISABLE, ui.select[ui.layer]);
                        break;
                    case 3:
                        break;
                    case 4:
                        check_box_s_select(KNOB_ROT_VOL, ui.select[ui.layer]);
                        break;
                    case 5:
                        check_box_s_select(KNOB_ROT_BRI, ui.select[ui.layer]);
                        break;
                    case 6:
                        break;
                }
        }
    }
}

// ��ť�㰴���ܲ˵�������
void kpf_proc(void)
{
    list_show(kpf_menu, M_KPF);
    if (btn.pressed)
    {
        btn.pressed = false;
        switch (btn.id)
        {
            case BTN_ID_CW:
            case BTN_ID_CC:
                list_rotate_switch();
                break;
            case BTN_ID_LP:
                ui.select[ui.layer] = 0;
            case BTN_ID_SP:
                switch (ui.select[ui.layer])
                {
                    case 0:
                        ui.index = M_KNOB;
                        ui.state = S_LAYER_OUT;
                        break;
                    case 1:
                        break;
                    case 2:
                        check_box_s_select(KNOB_DISABLE, ui.select[ui.layer]);
                        break;
                    case 3:
                        break;
                    case 4:
                        check_box_s_select('A', ui.select[ui.layer]);
                        break;
                    case 5:
                        check_box_s_select('B', ui.select[ui.layer]);
                        break;
                    case 6:
                        check_box_s_select('C', ui.select[ui.layer]);
                        break;
                    case 7:
                        check_box_s_select('D', ui.select[ui.layer]);
                        break;
                    case 8:
                        check_box_s_select('E', ui.select[ui.layer]);
                        break;
                    case 9:
                        check_box_s_select('F', ui.select[ui.layer]);
                        break;
                    case 10:
                        check_box_s_select('G', ui.select[ui.layer]);
                        break;
                    case 11:
                        check_box_s_select('H', ui.select[ui.layer]);
                        break;
                    case 12:
                        check_box_s_select('I', ui.select[ui.layer]);
                        break;
                    case 13:
                        check_box_s_select('J', ui.select[ui.layer]);
                        break;
                    case 14:
                        check_box_s_select('K', ui.select[ui.layer]);
                        break;
                    case 15:
                        check_box_s_select('L', ui.select[ui.layer]);
                        break;
                    case 16:
                        check_box_s_select('M', ui.select[ui.layer]);
                        break;
                    case 17:
                        check_box_s_select('N', ui.select[ui.layer]);
                        break;
                    case 18:
                        check_box_s_select('O', ui.select[ui.layer]);
                        break;
                    case 19:
                        check_box_s_select('P', ui.select[ui.layer]);
                        break;
                    case 20:
                        check_box_s_select('Q', ui.select[ui.layer]);
                        break;
                    case 21:
                        check_box_s_select('R', ui.select[ui.layer]);
                        break;
                    case 22:
                        check_box_s_select('S', ui.select[ui.layer]);
                        break;
                    case 23:
                        check_box_s_select('T', ui.select[ui.layer]);
                        break;
                    case 24:
                        check_box_s_select('U', ui.select[ui.layer]);
                        break;
                    case 25:
                        check_box_s_select('V', ui.select[ui.layer]);
                        break;
                    case 26:
                        check_box_s_select('W', ui.select[ui.layer]);
                        break;
                    case 27:
                        check_box_s_select('X', ui.select[ui.layer]);
                        break;
                    case 28:
                        check_box_s_select('Y', ui.select[ui.layer]);
                        break;
                    case 29:
                        check_box_s_select('Z', ui.select[ui.layer]);
                        break;
                    case 30:
                        break;
                    case 31:
                        check_box_s_select('0', ui.select[ui.layer]);
                        break;
                    case 32:
                        check_box_s_select('1', ui.select[ui.layer]);
                        break;
                    case 33:
                        check_box_s_select('2', ui.select[ui.layer]);
                        break;
                    case 34:
                        check_box_s_select('3', ui.select[ui.layer]);
                        break;
                    case 35:
                        check_box_s_select('4', ui.select[ui.layer]);
                        break;
                    case 36:
                        check_box_s_select('5', ui.select[ui.layer]);
                        break;
                    case 37:
                        check_box_s_select('6', ui.select[ui.layer]);
                        break;
                    case 38:
                        check_box_s_select('7', ui.select[ui.layer]);
                        break;
                    case 39:
                        check_box_s_select('8', ui.select[ui.layer]);
                        break;
                    case 40:
                        check_box_s_select('9', ui.select[ui.layer]);
                        break;
                }
        }
    }
}
//*****************************Main-Proc-Show****************************************//
//��ӽ�����Ĳ��� ����ӽ�����ʾ����������������ʾ
void serial_proc(void)
{
    list_show(serial_menu, M_SERIAL);
    if (btn.pressed)
    {
        btn.pressed = false;
        switch (btn.id)
        {
            case BTN_ID_CW:
            case BTN_ID_CC:
                list_rotate_switch();
                break;
            case BTN_ID_LP:
                ui.select[ui.layer] = 0;
            case BTN_ID_SP:
                switch (ui.select[ui.layer])
                {
                    case 0:// ���ظ�ǳ�㼶������������ѡ����һ�Ҳ��ִ����һ��
                        ui.index = M_MAIN;
                        ui.state = S_LAYER_OUT;
                        break;

                }
        }
    }

}
// ��ѹ����ҳ������
void volt_proc(void)
{
    volt_show();
    if (btn.pressed)
    {
        btn.pressed = false;
        switch (btn.id)
        {
            case BTN_ID_CW:
            case BTN_ID_CC:
                list_rotate_switch();
                break;

            case BTN_ID_SP:
            case BTN_ID_LP:
                ui.index = M_MAIN;
                ui.state = S_LAYER_OUT;
                break;
        }
    }
}

// ���ò˵�����������ѡ���б���ģ�壬����ģ��
void setting_proc(void)
{
    list_show(setting_menu, M_SETTING);
    if (btn.pressed)
    {
        btn.pressed = false;
        switch (btn.id)
        {
            case BTN_ID_CW:
            case BTN_ID_CC:
                list_rotate_switch();
                break;
            case BTN_ID_LP:
                ui.select[ui.layer] = 0;
            case BTN_ID_SP:
                switch (ui.select[ui.layer])
                {
                    // ���ظ�ǳ�㼶������������ѡ����һ�Ҳ��ִ����һ��
                    case 0:
                        ui.index = M_MAIN;
                        ui.state = S_LAYER_OUT;
                        break;
                        // �������ڣ�������ʼ�������⣬������������ֵ�����ֵ����Сֵ�������������б����������б��ǩ
                    case 1:
                        window_value_init("Disp Bri", DISP_BRI, &ui.param[DISP_BRI], 255, 0, 5, setting_menu, M_SETTING);
                        break;
                    case 2:
                        window_value_init("Tile Ani", TILE_ANI, &ui.param[TILE_ANI], 100, 10, 1, setting_menu, M_SETTING);
                        break;
                    case 3:
                        window_value_init("List Ani", LIST_ANI, &ui.param[LIST_ANI], 100, 10, 1, setting_menu, M_SETTING);
                        break;
                    case 4:
                        window_value_init("Win Ani", WIN_ANI, &ui.param[WIN_ANI], 100, 10, 1, setting_menu, M_SETTING);
                        break;
                    case 5:
                        window_value_init("Spot Ani", SPOT_ANI, &ui.param[SPOT_ANI], 100, 10, 1, setting_menu, M_SETTING);
                        break;
                    case 6:
                        window_value_init("Tag Ani", TAG_ANI, &ui.param[TAG_ANI], 100, 10, 1, setting_menu, M_SETTING);
                        break;
                    case 7:
                        window_value_init("Fade Ani", FADE_ANI, &ui.param[FADE_ANI], 255, 0, 1, setting_menu, M_SETTING);
                        break;
                    case 8:
                        window_value_init("Btn SPT", BTN_SPT, &ui.param[BTN_SPT], 255, 0, 1, setting_menu, M_SETTING);
                        break;
                    case 9:
                        window_value_init("Btn LPT", BTN_LPT, &ui.param[BTN_LPT], 255, 0, 1, setting_menu, M_SETTING);
                        break;
                        // ��ѡ��
                    case 10:
                        check_box_m_select(TILE_UFD);
                        break;
                    case 11:
                        check_box_m_select(LIST_UFD);
                        break;
                    case 12:
                        check_box_m_select(TILE_LOOP);
                        break;
                    case 13:
                        check_box_m_select(LIST_LOOP);
                        break;
                    case 14:
                        check_box_m_select(WIN_BOK);
                        break;
                    case 15:
                        check_box_m_select(KNOB_DIR);
                        break;
                    case 16:
                        check_box_m_select(DARK_MODE);
                        break;
                        // ���ڱ���
                    case 17:
                        ui.index = M_ABOUT;
                        ui.state = S_LAYER_IN;
                        break;
                }
        }
    }
}

// ���ڱ���ҳ
void about_proc(void)
{
    list_show(about_menu, M_ABOUT);
    if (btn.pressed)
    {
        btn.pressed = false;
        switch (btn.id)
        {
            case BTN_ID_CW:
            case BTN_ID_CC:
                list_rotate_switch();
                break;
            case BTN_ID_LP:
                ui.select[ui.layer] = 0;
            case BTN_ID_SP:{
                switch (ui.select[ui.layer])
                {
                    case 0:
                        ui.index = M_SETTING;
                        ui.state = S_LAYER_OUT;
                        break;
                }
            };break;
        }
    }
}

// �ܵ�UI����
void ui_proc(void)
{
    u8g2_SendBuffer(&u8g2);
    switch (ui.state)
    {
        case S_FADE:
            fade();
            break; // ת������
        case S_WINDOW:
            window_param_init();
            break; // ������ʼ��
        case S_CONFIRM_WINDOW:
            confirm_windos_param_init();
            break;// ȷ�ϵ�����ʼ��
        case S_LAYER_IN:
            layer_init_in();
            break; // �㼶��ʼ��
        case S_LAYER_OUT:
            layer_init_out();
            break; // �㼶��ʼ��
        case S_NONE:
            u8g2_ClearBuffer(&u8g2);
            switch (ui.index) // ֱ��ѡ��ҳ��
            {
                case M_WINDOW:
                    window_proc();
                    break;
                case M_CONFIRM_WINDOW:
                    confirm_window_proc();
                    break;
                case M_SLEEP:
                    sleep_proc();
                    break;
                case M_MAIN:
                    main_proc();
                    break;
                case M_EDITOR:
                    editor_proc();
                    break;
                case M_KNOB:
                    knob_proc();
                    break;
                case M_KRF:
                    krf_proc();
                    break;
                case M_KPF:
                    kpf_proc();
                    break;
                case M_VOLT:
                    volt_proc();
                    break;
                case M_SERIAL:
                    serial_proc();
                    break;
                case M_SETTING:
                    setting_proc();
                    break;
                case M_ABOUT:
                    about_proc();
                    break;
            }
    }
}
/*********************************** UI ��ʼ������ *********************************/

// �ڳ�ʼ��EEPROMʱ��ѡ���Գ�ʼ����Ĭ������
/**
  * @brief  ui_param_init �˵�������ʼ��
  * @note   None
  * @param  None
  * @retval None
  */
void ui_param_init(void)
{
    //0-255 �ٶ�Խ��Խ�� �ٶ�������delay
    ui.param[DISP_BRI] = 255; // ��Ļ����
    ui.param[TILE_ANI] = 50;  // ���������ٶ�
    ui.param[LIST_ANI] = 60;  // �б����ٶ�
    ui.param[WIN_ANI] = 20;   // ���������ٶ�
    ui.param[SPOT_ANI] = 50;  // �۹⶯���ٶ�
    ui.param[TAG_ANI] = 60;   // ��ǩ�����ٶ�
    ui.param[FADE_ANI] = 30;  // ��ʧ�����ٶ�
    ui.param[BTN_SPT] = 25;   // �����̰�ʱ��
    ui.param[BTN_LPT] = 150;  // ��������ʱ��
    ui.param[TILE_UFD] = 1;   // ����ͼ���ͷչ������
    ui.param[LIST_UFD] = 1;   // �˵��б��ͷչ������
    ui.param[TILE_LOOP] = 0;  // ����ͼ��ѭ��ģʽ����
    ui.param[LIST_LOOP] = 0;  // �˵��б�ѭ��ģʽ����
    ui.param[WIN_BOK] = 1;    // ���������黯����
    ui.param[KNOB_DIR] = 0;   // ��ť�����л�����
    ui.param[DARK_MODE] = 1;  // �ڰ�ģʽ����
}

/**
  * @brief  ui_init
  * @note   �б���ҳ���б�������ʼ���������ʼ���Ĳ���
  * @param  None
  * @retval None
  */
void ui_init(void)
{
    // ��ʼ���б�����
    // //��ӽ���������� ��Ӳ˵���ʼ��
    ui.num[M_MAIN] =    sizeof(main_menu)       / sizeof(M_SELECT);
    ui.num[M_EDITOR] =  sizeof(editor_menu)     / sizeof(M_SELECT);
    ui.num[M_KNOB] =    sizeof(knob_menu)       / sizeof(M_SELECT);
    ui.num[M_KRF] =     sizeof(krf_menu)        / sizeof(M_SELECT);
    ui.num[M_KPF] =     sizeof(kpf_menu)        / sizeof(M_SELECT);
    ui.num[M_VOLT] =    sizeof(volt_menu)       / sizeof(M_SELECT);
    ui.num[M_SERIAL] =  sizeof(serial_menu)     / sizeof(M_SELECT);
    ui.num[M_SETTING] = sizeof(setting_menu)    / sizeof(M_SELECT);
    ui.num[M_ABOUT] =   sizeof(about_menu)      / sizeof(M_SELECT);

//	ui_param_init();

    ui.index = M_MAIN;
    ui.state = S_LAYER_IN;
    u8g2_SetPowerSave(&u8g2, 0);
    ui.sleep = false;
    ui.fade = 1;

    win.l = (DISP_W - WIN_W) / 2;
    win.u = (DISP_H - WIN_H) / 2;

    con_win.l = (DISP_W - CON_WIN_W) / 2;
    con_win.u = (DISP_H - CON_WIN_H) / 2;

    list.line_n = DISP_H / LIST_LINE_H;

    tile.title_y_calc = TILE_INDI_S + (TILE_INDI_H - TILE_B_TITLE_H) / 2 + TILE_B_TITLE_H * 2;
    tile.title_y_trg_calc = TILE_INDI_S + (TILE_INDI_H - TILE_B_TITLE_H) / 2 + TILE_B_TITLE_H;

    knob.param[0] = KNOB_DISABLE; // �������б�ĵ�2��ѡ���0���Ǳ��⣬��1���Ƿֽ���
    knob.param[1] = KNOB_DISABLE; // �������б�ĵ�2��ѡ���0���Ǳ��⣬��1���Ƿֽ���
    knob.param[2] = 2; // �������б�ĵ�2��ѡ���0���Ǳ��⣬��1���Ƿֽ���
    knob.param[3] = 2; // �������б�ĵ�2��ѡ���0���Ǳ��⣬��1���Ƿֽ���
}


//���У��
unsigned short config_check(unsigned short *_data, unsigned char len)
{
    unsigned short ret = 0;
    for(unsigned char i = 0;i<len;i++)
    {
        ret+=_data[i];
    }
    return ret;
}
/************************************* �ϵ籣�� *************************************/
void eeprom_notify_change(void)
{
    eeprom_change = true;
}

//�ڴ�����˳��UI����+������תʱ��+��������+У��
#define USER_CONFIG_SIZE	UI_PARAM + 1 + 4 + 1
// u8g2  UI���������ͳ�ʼ������
void u8g2_init(void)
{
    buf_ptr = u8g2_GetBufferPtr(&u8g2);
    buf_len = 8 * u8g2_GetBufferTileHeight(&u8g2) * u8g2_GetBufferTileWidth(&u8g2);
    u8g2_SetContrast(&u8g2, ui.param[DISP_BRI]);
}

/**
  * @brief  gui_btn_send_signal �������ݺ���
  * @note   None
  * @param  btn_id �������
  * @param  event ����״̬
  * @retval None
  */
void gui_btn_send_signal(uint8_t btn_id, uint8_t event)
{
    static uint8_t flag[3] = {0}; // ��������ɿ����ᴥ��һ�°���̧��ģ��ַ���һ�ε�����
    if (btn_id == 1 && event == PRESS_UP)
    {
        if (flag[0] == 0)
        {
            btn.id = BTN_ID_CC;//���󰴼�����
            btn.pressed = true;
            led_setup(50, 0.5f, 1);
        }
        else
        {
            flag[0] = 0;
        }
    }
    else if (btn_id == 2 && event == PRESS_UP)
    {
        if (flag[1] == 0)
        {
            btn.id = BTN_ID_SP;//ȷ�ϰ�������
            btn.pressed = true;
            led_setup(50, 0.5f, 1);
        }
        else
        {
            flag[1] = 0;
        }
    }
    else if (btn_id == 3 && event == PRESS_UP)
    {
        if (flag[2] == 0)
        {
            btn.id = BTN_ID_CW;//���ұ߰�������
            btn.pressed = true;
            led_setup(50, 0.5f, 1);
        }
        else
        {
            flag[2] = 0;
        }
    }
    else if (btn_id == 1 && event == LONG_PRESS_HOLD)
    {
        btn.id = BTN_ID_CC;
        btn.pressed = true;
        flag[0] = 1;
    }
    else if (btn_id == 2 && event == LONG_PRESS_START)
    {
        btn.id = BTN_ID_LP;
        btn.pressed = true;
        flag[1] = 1;
    }
    else if (btn_id == 3 && event == LONG_PRESS_HOLD)
    {
        btn.id = BTN_ID_CW;
        btn.pressed = true;
        flag[2] = 1;
    }
}


/**
  * @brief  task_gui_proc �˵�����
  * @note   None
  * @param  None
  * @retval None
  */
void task_gui_proc(void)
{
    ui_proc();
}

/**
  * @brief  myGui_init �˵������ʼ��
  * @note   None
  * @param  None
  * @retval None
  */
void myGui_init(void)
{
    ui_param_init();
    u8g2Init(&u8g2);
    ui_init();
    u8g2_init();
}