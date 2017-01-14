# 用于编写数控仿真程序的工具类
---

## 依赖库

1. MFC相关类库
2. OpenGL库
3. glm库

---

## 开始使用

> OpenGL固定管线

1 继承自BaseCompatGL。

```C++
public class MyGL : public BaseCompatGL{

}
```

2 重写 *void draw(void)* 方法。

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

3 在MFC的CView类创建子类对象，在OnCreate中创建环境，在OnDestroy中删除环境

```C++
	int CView::OnCreate(...){
		//TO DO
		//m_myGL为MyGL的实例
		m_myGL.createContext(this);
		m_myGL.init();
		m_myGL.setBackgroundColorTop(0.5f,0.5f,0.5f);
	}
	
	int CView::OnDestroy(...){
		//TO DO
		m_myGL.deleteContext();
	}
```

4 在CView类需要的地方调用draw()方法。
```C++
	m_myGL.draw();
```