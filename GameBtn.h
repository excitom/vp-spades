#ifndef _UBQ_GAME_BUTTON_H_
#define _UBQ_GAME_BUTTON_H_

#define BTN_UP_NO_FOCUS 0
#define BTN_UP_FOCUS    1
#define BTN_DOWN        2
#define BTN_DISABLED    3

#define TOGGLE_NO_FOCUS		0
#define TOGGLE_FOCUS		1
#define TOGGLE_DISABLED		4

class CUbqGameButton : public CUbqMultImage
{
  // construction
  public:
    CUbqGameButton(int id, CRect Area, CUbqGameBoard*  p_board, BOOL IsToggle=FALSE);
    ~CUbqGameButton();

  // methods
  public:
    int GetID() { return m_id;}

    void MouseUp();
    void MouseDown();
    void SetDisabled(BOOL bIsDisables);
    void SetInFocus(BOOL bIsInFocus);
    void SetEnabledInFocus();
    
    BOOL IsDisabled() { if (m_bIsToggle)
							return(GetStatus() == TOGGLE_DISABLED); 
						else
							return(GetStatus() == BTN_DISABLED) ;   }
    BOOL IsDown()     { if (m_bIsToggle)
							return FALSE; 
						else
							return(GetStatus() == BTN_DOWN); }
    BOOL IsUpNoFocus(){ if (m_bIsToggle)
							return(GetStatus() == TOGGLE_NO_FOCUS+m_nToggleFrame); 
						else
							return(GetStatus() == BTN_UP_NO_FOCUS); }
    BOOL IsUpFocus()  { if (m_bIsToggle)
							return(GetStatus() == TOGGLE_FOCUS+m_nToggleFrame); 
						else
							return(GetStatus() == BTN_UP_FOCUS); }

	// toggle buttons support. 
	void SetToggle  (BOOL ToggleOn) {m_nToggleFrame = (ToggleOn?0:2);}
	BOOL IsToggleOn ()				{return m_nToggleFrame==2;}

  // members
  private:
    int  m_id;
	BOOL m_bIsToggle;
	int  m_nToggleFrame;
};

#endif // _UBQ_GAME_BUTTON_H_

