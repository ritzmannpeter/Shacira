class CUGArrowType: public CUGCellType{

public:

	CUGArrowType();
	~CUGArrowType();
	virtual void OnDraw(CDC *dc,RECT *rect,int col,long row,CUGCell *cell,
						int selected,int current);

};