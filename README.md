# ���ڱ�д���ط������Ĺ�����
---

## ������

1. MFC������
2. OpenGL��
3. glm��

---

## ��ʼʹ��

> OpenGL�̶�����

1 �̳���BaseCompatGL��

```C++
public class MyGL : public BaseCompatGL{

}
```

2 ��д *void draw(void)* ������

```C++
public class MyGL : public BaseCompatGL{
	...
	void draw(void){
		drawBacground();
		show();
	}
	...
}
```

3 ��MFC��CView�ഴ�����������OnCreate�д�����������OnDestroy��ɾ������

```C++
	int CView::OnCreate(...){
		//TO DO
		//m_myGLΪMyGL��ʵ��
		m_myGL.createContext(this);
		m_myGL.init();
		m_myGL.setBackgroundColorTop(0.5f,0.5f,0.5f);
	}
	
	int CView::OnDestroy(...){
		//TO DO
		m_myGL.deleteContext();
	}
```

4 ��CView����Ҫ�ĵط�����draw()������
```C++
	m_myGL.draw();
```