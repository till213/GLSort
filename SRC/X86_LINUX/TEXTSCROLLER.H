#define MAX_MSG_LEN	42

typedef char Message[MAX_MSG_LEN];

void initTextScroller (void);
void writeScrollerLine (const Message text);
void drawTextScroller (void);
