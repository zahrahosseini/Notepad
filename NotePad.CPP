#include<iostream.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
//cursor max 80,25
int xpos=1,ypos=1;
struct Flist;
struct Llist;
struct ListNode;
enum bool {true=1,false=0};
struct Flist {
	Flist *next;
	Flist *prev;
	Llist *llist;
	ListNode *lchar;
}*head=NULL;
struct Llist{
	Llist *next;
	Llist *prev;
	Flist *flist;
	ListNode *lchar;
}*tail=NULL;
struct ListNode {
	ListNode *next;
	ListNode *prev;
	Llist *llist;
	Flist *flist;
	int value;
}*current=NULL;
int StartPos=0,StartPosY=0;
int _startx=1;
Flist* Create(ListNode* list)
{
	head=new Flist();
	tail=new Llist();
	list=new ListNode();
	head->lchar=list;
	tail->lchar=list;
	list->value=0;
	list->flist=head;
	list->llist=tail;
	head->llist=tail;
	tail->flist=head;
	list->next=list->prev=NULL;
	head->next=head->prev=NULL;
	tail->next=tail->prev=NULL;
	return head;
}
template <class temp> void MakeNull(temp* list)
{
	if(!list) return;
	MakeNull(list->next);
	delete(list);
	list=NULL;
}
int SetLoc(ListNode* cur)
{
int xpos=0;
ListNode* fcur=cur->flist->lchar;
while(fcur)
{
if(fcur==cur)
break;
else
{fcur=fcur->next;
xpos++;
}
}
return xpos+1;
}
ListNode* FirstTab(ListNode* first,int & num)
{
	ListNode* Ftab;
	num=0;
	while(first)
	{
		if(first->value==1)
		{
			num=1;
			Ftab=first;
			if((first->next->value==1)||(first->next->value>9))
			{
				num=1;
				return Ftab;
			}
			else
				if((first->next->value>1)&&(first->next->value<9))
				{
					num=2;
					first=first->next;
					while((first->value>1)&&(first->value<9))
					{
						if((first->value>1)&&(first->value<9))
						{
							first=first->next;
							num++;
						}
						else
						return Ftab;
					}
					return Ftab;
				}
		}
		else
		if(first->next) first=first->next;
		else return NULL;
	}
	return NULL;
}
ListNode* Insert(ListNode* cur,int _value)
{
	ListNode* tmp=new ListNode();
	tmp->value=_value;
	tmp->flist=cur->flist;
	tmp->llist=cur->llist;
	if(cur->next)
	{
		tmp->next=cur->next;
		cur->next->prev=tmp;
	}
	else
	{
		cur->llist->lchar=tmp;
		tmp->next=NULL;
	}
	cur->next=tmp;
	tmp->prev=cur;
	cur->flist->lchar->value+=1;
	return cur->next;
}
void MakeNullAll(ListNode *_List)
{
	Flist* first=_List->flist;
	while (first)
	{
		if(first->prev)first=first->prev;
		else break;
	}
	while(first)
	{
		MakeNull(first->lchar);
		if(first->next) first=first->next;
		else break;
	}
	while (first)
	{
		if(first->prev)first=first->prev;
		else break;
	}
	Llist *last=first->llist;
	MakeNull(last);
	MakeNull(first);
}
ListNode* Dispose( ListNode* cur)
{
	ListNode* tmp=cur->prev;
	cur->flist->lchar->value--;
	if(cur->next)
	{
		tmp->next=cur->next;
		cur->next->prev=tmp;
	}
	else
	{
		cur->flist->llist->lchar=tmp;
		tmp->next=NULL;
	}
	delete(cur);
	return tmp;
}
Flist* DeleteList(Flist* list)
{
	MakeNull(list->lchar);
	Flist * thead;
	if((list->prev)&&(list->next))
	{
		thead=list->prev;
		thead->next=list->next;
		list->next->prev=thead;
		thead->llist->next=list->llist->next;
		list->next->llist->prev=thead->llist;
		delete(list->llist);
		delete(list);
	}
	else
	{
		if((list->next==NULL)&&(list->prev))
		{
			thead=list->prev;
			delete(list->llist);
			delete(list);
			thead->next=NULL;
			thead->llist->next=NULL;
		}
	}
	return thead;
}
Flist * GOFirst(ListNode* cur)
{
	Flist * thead=cur->flist;
	while(thead)
	if(thead->prev)
	thead=thead->prev;
	else
	break;
	gotoxy(1,1);
	return thead;
}
ListNode* GOLast(ListNode *cur,int &xpos,int&ypos);
void Delete(ListNode* cur)
{
	int x,y;
	if(cur!=GOLast(cur,x,y))
	if(cur!=cur->llist->lchar)
	{
		if(cur->next==cur->llist->lchar)
		{
			if(cur->flist->next)
			{
				ListNode* tmp=cur->flist->next->lchar->next;
				ListNode * tcur=cur->next;
				while(tmp)
				{
					tcur=Insert(tcur,tmp->value);
					if(tmp->next)
					tmp=tmp->next;
					else
					break;
				}
				DeleteList(tmp->flist);
			}
		}
		else
		{
			if(cur->next->value!=1)
			{
				if(cur->next->next->value!=1)
				{
					ListNode* tmp=cur->next->next;
					Dispose(tmp);
				}
				else
				{
					ListNode* tmp=cur->next->next;
					int sum;
					tmp=FirstTab(tmp->prev,sum);
					tmp=Dispose(tmp);
					if(sum>0)
					{
					tmp=tmp->next;
						for(int i=1;i<sum-1;i++)
						{
							tmp=Dispose(tmp);
							if(tmp->next)tmp=tmp->next;
						
						}
					}
				}
			}
			else
			if(cur->next->value==1)
			{
				ListNode* tmp=cur->next;
				int sum;
					tmp=FirstTab(tmp->prev,sum);
					tmp=Dispose(tmp);
					if(sum>0)
					{
					tmp=tmp->next;
						for(int i=1;i<sum-1;i++)
						{
							tmp=Dispose(tmp);
							if(tmp->next)tmp=tmp->next;
						
						}
					}
			}
		}
	}
	else
	{
		ListNode* tmp=cur->flist->next->lchar;
		ListNode* tcur=cur->llist->lchar;
		if(tmp->next)
		{
			tmp=tmp->next;
			while(tmp)
			{
				tcur=Insert(tcur,tmp->value);
				if(tmp->next)
				tmp=tmp->next;
				else
				break;
			}
		}
		DeleteList(tmp->flist);
	}
}
ListNode* BackSpace(ListNode* cur, int& xpos, int& ypos)
{
	Flist * tfirst=GOFirst(cur);
	if(cur!=cur->flist->lchar)
	{
		if(cur->value>9)
		{
			cur=Dispose(cur);
			xpos--;
			return cur;
		}
		else
		{
			int count=cur->value;
			for(int i=0;i<count;i++)
			{cur=Dispose(cur);
			xpos--;}
			return cur;
		}
	}
	else
	if((cur==cur->flist->lchar)&&(cur->flist!=tfirst))
	{
		ListNode* uplist=cur->llist->prev->lchar;
		ListNode* UPlist=uplist;
		xpos=uplist->flist->lchar->value+1;
		ypos--;
		if(cur->next)
		{
			cur=cur->next;
			while(cur)
			{
				uplist=Insert(uplist,cur->value);
				if(cur->next)
				cur=cur->next;
				else
				break;
			}
		}
		DeleteList(cur->flist);
		////////////
		int txpos=xpos;
				ListNode* tmp=UPlist->prev;
				int sum=0;
				tmp=FirstTab(tmp,sum);
					if(sum!=0)
					{
						ListNode* s=UPlist;
						while(s)
						{
							if(s==tmp)
							break;
							else
								if(s->next)
								{
									s=s->next;
									txpos++;
								}
								else
								break;
						}
						tmp=tmp->prev->prev;
						Delete(tmp);
						tmp=tmp->next;
						txpos--;
						int counter=7-(txpos-1)%8;
				for(int i=1;i<counter+1;i++)
				{
					tmp=Insert(tmp,i);
				}
					}
		/////////////
		return UPlist;
	}
	else
	if(cur->flist==tfirst)
	return cur;
	return NULL;
}
void Print(Flist *first,int start)
{
	ListNode* tlist=first->lchar;
	if(tlist->value>start)
	{
		tlist=tlist->next;
		for(int i=0;i<start;i++)
		tlist=tlist->next;
		for(int h=start;h<(start+80);h++)
		{
		if(tlist->value<9)
			cout<<" ";
			else
			cout<<(char)tlist->value;
			if(tlist->next)
			tlist=tlist->next;
			else
			break;
		}
	}
}
void PrintAll(Flist *first ,int start)
{
Flist * thead=first;
	gotoxy(0,0);
	int j=0;
	while(thead)
	{
		Print(thead,start);
		if((thead->next)&&(j<24))
	       {
		   if(thead->lchar->value<80)
	       cout<<endl;
	       thead=thead->next;
	       }
		else
		break;
		j++;
	}
}
Flist* CreateNewList(ListNode* list)
{
	Flist* thead=Create(list);
	Flist* mlist=list->flist;
	if(mlist->next)
	{
		thead->next=mlist->next;
		mlist->next->prev=head;
		head->llist->next=mlist->llist->next;
		mlist->llist->next->prev=head->llist;
	}
	mlist->next=thead;
	thead->prev=mlist;
	mlist->llist->next=thead->llist;
	thead->llist->prev=mlist->llist;
	return thead;
}
Flist* EnterPressed(ListNode* cur,int& xpos,int& ypos)
{
	ListNode* thead=CreateNewList(cur)->lchar;
	ListNode* tcur=cur;
	if(tcur->next)
	{
		tcur=tcur->next;
		while(tcur)
		{
			thead=Insert(thead,tcur->value);
			if(tcur->next)
			tcur=tcur->next;
			else
			break;
		}
		cur->flist->lchar->value=xpos-1;
		cur->llist->lchar=cur;
		MakeNull(cur->next);
		cur->next=NULL;
	}
	ypos++;
	xpos=1;
	return thead->flist;
}
ListNode* GORight(ListNode* cur,int& xpos,int& ypos)
{
	if(cur->next)
	{
		if(cur->next->value!=1)
		{
			cur=cur->next;
			xpos++;
		}
		else
		{
			cur=cur->next;
			xpos++;
			if(cur->next->value==2)
			{
				cur=cur->next;
				xpos++;
				while((cur->value>1)&&(cur->value<9))
				{
					if((cur->next)&&(cur->next->value>1)&&(cur->next->value<9))
					{
						cur=cur->next;
						xpos++;
					}
					else
					break;
				}
			}
		}
	}
	else
	if(cur->flist->next)
	{
		cur=cur->flist->next->lchar;
		xpos=1;
		ypos++;
	}
	return cur;
}
ListNode* GOLeft(ListNode *cur,int& xpos,int& ypos)
{
	if((xpos>1)||(ypos>1))
	if(cur!=cur->flist->lchar)
	{
		if((cur->value>9))
		{
			cur=cur->prev;
			xpos--;
		}
		else
		{
			if(cur->value<9)
			{
				while(cur->value!=1)
				{
					if(cur->prev)
					{
						cur=cur->prev;
						xpos--;
					}
					else
					break;
				}
				if(cur->prev)
				{
					cur=cur->prev;
					xpos--;
				}
			}
			else
			{
				cur=cur->next;
				xpos--;
			}
		}
	}
	else
	{
		cur=cur->flist->prev->llist->lchar;
		ypos--;
		xpos=cur->flist->lchar->value+1;
	}
	return cur;
}
ListNode* GOUp(ListNode* cur,int& xpos,int& ypos)
{
	if(cur->flist->prev!=NULL)
	{
		ListNode* tcur=cur->flist->prev->lchar;
		if(xpos>tcur->value)
		{
			ypos--;
			xpos=tcur->flist->lchar->value+1;
			cur=tcur->llist->lchar;
			return cur;
		}
		else
		{
			ListNode* tmp=cur->flist->prev->lchar;
			ypos--;
			int   mxpos=0;
			for(int i=0;i<xpos;i++)
			{
				tmp=tmp->next;
				mxpos++;
			}
			tmp=tmp->prev;
			ListNode* mtmp;
			if(tmp->value<9)
			{
				int tx=tmp->value;
				mtmp=tmp;
				while(mtmp)
				{
					if((mtmp->next->value>9)||(mtmp->next->value==1))
					break;
					else
					if(mtmp->next) mtmp=mtmp->next;
					else
					break;
				}
				int txx=mtmp->value/2;
				if(tx>=txx)
				{
					mxpos+=mtmp->value-tx;
					tmp=mtmp;
				}
				else
				{
					while(tmp)
					{
						if(tmp->value==1)
						break;
						else
						if(tmp->prev)
						{
							tmp=tmp->prev;
							mxpos--;
						}
					}
					tmp=tmp->prev;
					mxpos--;
				}
			}
			xpos=mxpos;
			return tmp;
		}
	}
	else
	return cur;
}
ListNode* GODown(ListNode* cur,int& xpos,int& ypos)
{
	if(cur->flist->next)
	if(xpos>cur->flist->next->lchar->value)
	{
		cur=cur->llist->next->lchar;
		ypos++;
		xpos=cur->flist->lchar->value+1;
		return cur;
	}
	else
	{
		ListNode* tmp=cur->flist->next->lchar;
		ypos++;
		int mxpos=1;
		for(int i=0; i<xpos;i++)
		{
			tmp=tmp->next;
			mxpos++;
		}
		tmp=tmp->prev;
		
		ListNode* mtmp;
		if(tmp->value<9)
			{
				int tx=tmp->value;
				mtmp=tmp;
				while(mtmp)
				{
					if((mtmp->next->value>9)||(mtmp->next->value==1))
					break;
					else
					if(mtmp->next) mtmp=mtmp->next;
					else
					break;
				}
				int txx=mtmp->value/2;
				if(tx>=txx)
				{
					mxpos+=mtmp->value-tx;
					tmp=mtmp;
				}
				else
				{
					while(tmp)
					{
						if(tmp->value==1)
						break;
						else
						if(tmp->prev)
						{
							tmp=tmp->prev;
							mxpos--;
						}
					}
					tmp=tmp->prev;
					mxpos--;
				}
			}
			xpos=mxpos-1;
		return tmp;
	}
	else
	return cur;
}
void Save(ListNode* Current)
{
	clrscr();
	cout<<"Write your file name to save :" <<endl;
	char* filename=new char[10];
	cin>>filename;
	FILE* pFile = fopen (filename,"wb+");
	fflush(pFile);
	char s;
	////////////////////
	Flist* first=GOFirst(Current);
	while(first)
	{
		ListNode* tlist=first->lchar;
		{
			tlist=tlist->next;
			for(int h=0;h<tlist->flist->lchar->value;h++)
			{
				s=(char)tlist->value;
				fwrite(&s,sizeof(s),1,pFile);
				if(tlist->next)
				tlist=tlist->next;
				else
				break;
			}
		}
		if((first->next))
		{
			fprintf(pFile,"%c",':');
			first=first->next;
		}
		else
		break;
	}
	 fclose (pFile);
	 exit(0);
}
ListNode* Open(char* filename)
{
	gotoxy(1,1);
	xpos=ypos=1;
	FILE* f=fopen(filename,"rb");
	ListNode* cur=new ListNode();
	cur=Create(cur)->lchar;
	char s;
	while (!feof(f))
	{
		s=fgetc(f);
		if(s!=':')
		cur=Insert(cur,(int)s);
		else
		cur=EnterPressed(cur, xpos, ypos)->lchar;
    }
	cur=GOFirst(cur)->lchar;
	clrscr();
	gotoxy(1,1);
	PrintAll(cur->flist,0);
	cur=GOFirst(cur)->lchar;
	gotoxy(1,1);
	return cur;
}
ListNode* GOLast(ListNode *cur,int &xpos,int&ypos)
{
	Flist *first=GOFirst(cur);
	xpos=ypos=0;
	gotoxy(0,0);
	while(first)
	{
		if(first->next)
		{
			first=first->next;
			ypos++;
		}
		else
		break;
	}
	xpos=first->lchar->value;
	cur=first->lchar;
	for(int i=0;i<xpos;i++)
	cur=cur->next;
	return cur;
}
int main()
{
	clrscr();
	ListNode *Current=new ListNode();
	head=Create(Current);
	Current=head->lchar;
	char c=getch();
	int n=(int)c;
	while(n!=27)
	{
		if(n==0)
		{
			c=getch();
			n=(int) c;
			if(n==72) //Up
			{
				Current=GOUp(Current,xpos,ypos);

				Flist * thead=GOFirst(Current);
				_startx=xpos;
				if(ypos<=25)thead=GOFirst(Current);
				else
				{
					for(int i=0;i<ypos-25;i++)
					if(thead->next)
					thead=thead->next;
					else
					break;
				}


				PrintAll(thead,StartPos);
				if(ypos<25)
				gotoxy(_startx,ypos);
				else
				gotoxy(_startx,25);
			}
			else
			if(n==80) //Down
			{
				Current=GODown(Current,xpos,ypos);
				Flist * thead=GOFirst(Current);
				_startx=xpos;

				if(ypos<=25) thead=GOFirst(Current);
				else
				{
					for(int i=0;i<ypos-25;i++)
					if(thead->next)
					thead=thead->next;
					else
					break;
				}
				PrintAll(thead,StartPos);
				if(ypos<25)
				gotoxy(_startx,ypos);
				else
				gotoxy(_startx,25);
			}
			else
			if(n==77) //Right
			{
				ListNode* c=Current;
				Current=GORight(Current,xpos,ypos);
				if(c!=Current)
				if(xpos>80)
				{
					StartPos++;
					_startx=80;
					gotoxy(_startx,ypos);
				}
				else
				{
					_startx=xpos;
					gotoxy(_startx,ypos);
					StartPos=0;
				}
			}
			else
			if(n==75) //Left
			{
				Current=GOLeft(Current,xpos,ypos);
				if(xpos>80)
				{
					StartPos++;
					_startx=80;
					gotoxy(_startx,ypos);
				}
				else
				{
					_startx=xpos;
					gotoxy(_startx,ypos);
					StartPos=0;
				}
			}
			else
			if(n==83) //Delete
			{
				if((Current->next->next->value<9)||(Current==Current->llist->lchar))
				{
				Delete(Current);
				int txpos=xpos;
				ListNode* tmp=Current;
				int sum=0;
				tmp=FirstTab(tmp,sum);
					if(sum!=0)
					{
						ListNode* s=Current;
						while(s)
						{
							if(s==tmp)
							break;
							else
								if(s->next)
								{
									s=s->next;
									txpos++;
								}
								else
								break;
						}
						tmp=tmp->prev->prev;
						Delete(tmp);
						tmp=tmp->next;
						txpos--;
						int counter=8-(txpos-1)%8;
				for(int i=1;i<counter+1;i++)
				{
					tmp=Insert(tmp,i);
				}
					}
				}
				else
				if((Current->next->value>9))
				{
					Delete(Current);
					//////////////////////////////
					ListNode* t;
					if(Current!=Current->flist->lchar)
					 t=Current;
					else
					 t=Current->next;
					int s=0;
					ListNode* firsttab=FirstTab(t,s);
					if((s<9)&&(s>0))
					
					{
						if(s>1)
						{
							for(int i=1;i<s;i++)
							{
									if((firsttab->next)&&(firsttab->next->value<9))
									firsttab=firsttab->next;
									else
								break;
							}
						Insert(firsttab,s);
						}
					else
						Insert(firsttab,s+1);
					}
					else
					if(s>0)
					{
						for(int i=0;i<8;i++)
						{
							if(firsttab->next)
							firsttab=firsttab->next;
							else
							break;
						}
						if((firsttab==firsttab->llist->lchar)&&(firsttab->value>9))
						firsttab=firsttab->prev;
							else
						if(firsttab->next)
						firsttab=firsttab->prev;
						for(int j=1;j<8;j++)
						if(firsttab->value<9)
						firsttab=Dispose(firsttab);
					}
			//////////////////////////////
				}
			}
			else
			if(n==71)  //Home
			{
				xpos=ypos=1;
				_startx=xpos;
				gotoxy(_startx,ypos);
				StartPos=0;
				Current=GOFirst(Current)->lchar;
			}
			else
			if(n==79) //End
			{
				Current=GOLast(Current,xpos,ypos);
				xpos++;
				ypos++;
				if(xpos>80)
				StartPos=xpos-80;
				_startx=xpos;
				gotoxy(_startx,ypos);
			}
		}
		else
		if(n==19)//Ctrl+s
		{
		
		Save(Current);
		}
		else
		if(n==15) //Ctrl+o
		{
		clrscr();
		cout<<"Write your filename to open :"<<endl;
		char* filename=new char[10];
		cin>>filename;
		FILE* f=fopen(filename,"rb");
		if(f!=NULL)
		{
			Current=GOFirst(Current)->lchar;
			 Current=Open(filename);
		}
		}
		else
		if(n==1) //Ctrl+A
		{
			xpos=1;
			Current=Current->flist->lchar;
		}
		else
		if(n==12) //Ctrl+L
		{
			xpos=Current->flist->lchar->value+1;
			Current=Current->llist->lchar;
		}
		else
		if(n==8) //BackSpace
		{
			if((xpos!=1)||(ypos!=1))
			if(Current->value<9)
			{
			Current=BackSpace(Current,xpos,ypos);
			////////////////////////////
			int txpos=xpos;
				ListNode* tmp=Current;
				int sum=0;
				tmp=FirstTab(tmp,sum);
					if(sum!=0)
					{
						ListNode* s=Current;
						while(s)
						{
							if(s==tmp)
							break;
							else
								if(s->next)
								{
									s=s->next;
									txpos++;
								}
								else
								break;
						}
						tmp=tmp->prev->prev;
						Delete(tmp);
						tmp=tmp->next;
						txpos--;
						int counter=8-(txpos-1)%8;
				for(int i=1;i<counter+1;i++)
				{
					tmp=Insert(tmp,i);
				}
					}
			///////////////////////////////
			}
			else
			{

			Current=BackSpace(Current,xpos,ypos);
			if(Current!=Current->llist->lchar)
			{
			//////////////////////////////
			ListNode* t=Current;
			int s=0;
			ListNode* firsttab=FirstTab(t,s);
			if((s<9)&&(s>0))
			{
				if(s>1)
				{
					for(int i=1;i<s;i++)
					{
						if((firsttab->next)&&(firsttab->next->value<9))
						firsttab=firsttab->next;
						else
						break;
					}
					Insert(firsttab,s);
				}
				else
					Insert(firsttab,s+1);
			}
			else
				if(s>0)
				{
					for(int i=0;i<8;i++)
					{
						if(firsttab->next)
						firsttab=firsttab->next;
						else
						break;
					}

					if(firsttab==firsttab->llist->lchar)
					firsttab=firsttab->prev;
					else
					if(firsttab->next)
					firsttab=firsttab->prev;
					for(int j=1;j<8;j++)
					if(firsttab->value<9)
					firsttab=Dispose(firsttab);
				}
			//////////////////////////////
			}
			}
			gotoxy(_startx,ypos);
			gotoxy(0,0);
			Flist * thead=GOFirst(Current);
			if(xpos<80)
			_startx=xpos;
			else
			_startx=80;
			if(ypos<=25) thead=GOFirst(Current);
			else
			{
				for(int i=0;i<ypos-25;i++)
				if(thead->next)
				thead=thead->next;
				else
				break;
			}
			if(xpos>80)
			StartPos=xpos-80;
			else
			StartPos=0;
			PrintAll(thead,StartPos);
			gotoxy(_startx,ypos);
		}
		else
		if(n==13)//Enter
		{
			Current=EnterPressed(Current, xpos, ypos)->lchar;
			StartPos= 0;
			Flist * thead=GOFirst(Current);
			_startx=xpos;
			if(ypos<=25)thead=GOFirst(Current);
			else
			{
				for(int i=0;i<ypos-25;i++)
				if(thead->next)
				thead=thead->next;
				else
				break;
			}

			PrintAll(thead,StartPos);
			gotoxy(_startx,ypos);
		}

		else
		if(n==9) //Tab
		{
			int counter=8-(xpos-1)%8;
			for(int i=1;i<counter+1;i++)
			{
				Current=Insert(Current,i);
			}
			if(!Current->next)
			xpos=Current->flist->lchar->value;
			xpos+=counter;
			int txpos=xpos;
				ListNode* tmp=Current;
				int sum=0;
				tmp=FirstTab(tmp,sum);
					if(sum!=0)
					{
						ListNode* s=Current;
						while(s)
						{
							if(s==tmp)
							break;
							else
								if(s->next)
								{
									s=s->next;
									txpos++;
								}
								else
								break;
						}
						tmp=tmp->prev->prev;
						Delete(tmp);
						tmp=tmp->next;
						txpos--;
						int counter=8-(txpos-1)%8;
				for(int i=1;i<counter+1;i++)
				{
					tmp=Insert(tmp,i);
				}
					}
			if(xpos>80)
			{
				StartPos=xpos-80;
				_startx=80;
			}
			else
			{
			StartPos=0;
			_startx=xpos;
			}
		}

		else
		if(((n>64)&&(n<91))||((n>96)&&(n<123))||((n>47)&&(n<58))||(n==32))
		{
			Current=Insert(Current,n);
			xpos++;
		       //	if(!Current->next)
		       //	xpos=Current->flist->lchar->value+1;
		      //	else
			xpos=SetLoc(Current);
			if(xpos>80)
			{
				StartPos=xpos-80;
				_startx=80;
			}
			else
			{
			StartPos=0;
			_startx=xpos;
			}
			clrscr();
			gotoxy(0,0);
			Flist * thead=GOFirst(Current);
			if(ypos<=25)
			thead=GOFirst(Current);
			else
			{
				for(int i=0;i<ypos-25;i++)
				if(thead->next)
				thead=thead->next;
				else
				break;
			}
			xpos=SetLoc(Current);
			if(xpos>80)
			StartPos=xpos-80;
			else
			StartPos=0;
			PrintAll(thead,StartPos);
			if(xpos>80)
			_startx=80;
			else
			_startx=xpos;
			if(ypos<25)
			gotoxy(_startx,ypos);
			else
			gotoxy(_startx,25);
			///////////////////////////////
			ListNode* t=Current;
			int s=0;
			ListNode* firsttab=FirstTab(t,s);
			if(s==1)
			for(int i=2;i<9;i++)
			{
				firsttab=Insert(firsttab,i);
			}
			else
			{
			for(int i=1;i<s;i++)
			{
				if(firsttab->next)
				firsttab=firsttab->next;
				else
				break;
			}
			Dispose(firsttab->prev);
			}

			////////////////////////////
		}
		clrscr();
		gotoxy(0,0);
		xpos=SetLoc(Current);
		Flist * thead=GOFirst(Current);
		if(ypos<=25)
		thead=GOFirst(Current);
		else
		{
			for(int i=0;i<ypos-25;i++)
			if(thead->next)
			thead=thead->next;
			else
			break;
		}
		xpos=SetLoc(Current);
		if(xpos>80)
		StartPos=SetLoc(Current)-80;
		else
	      StartPos=0;
		PrintAll(thead,StartPos);
		if(xpos>80)
		_startx=80;
		else
		_startx=xpos;
		if(ypos<25)
		gotoxy(_startx,ypos);
		else
		gotoxy(_startx,25);
		c=getch();
		n=(int)c;
		if(n==27)
		break;
	}
	Flist * thead=GOFirst(Current);
	PrintAll(thead,StartPos);
	MakeNull(Current);
	getch();
	return 0;
}
