function [s] = FuhuaTixing241()
%�������ι�ʽ��sqrt(4-sin(x)^2)����(0~1/4)

%����
f = inline('sqrt(4-sin(x)^2)','x');

%��ʼֵ
a = 0;%�½�
b = 1/4;%�Ͻ�
M = 10;

%���
h=(b-a)/M;
s=0;
for k=1:(M-1)
   x=a+h*k;
   s=s+f(x);
end

s=h*(f(a)+f(b))/2+h*s;

%��ͼ
x = 0:1/100:1/4;
y = sqrt(4-sin(x).^2);
%ԭ����
plot(x,y,'g');
hold on;
%����
px = a;
for k=1:M
    line([a,a+h],[f(a),f(a+h)]);
    hold on;
    line([a,a],[1.984,f(a)]);
    hold on;
    a = a+h;
end
line([b,b],[1.984,f(b)]);
end
