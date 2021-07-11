function [s] = FuhuaSimpson242()
%����Simpson��ʽ��exp(x)/(4+x^2)����(0~1)

%����
f = inline('exp(x)/(4+x^2)','x');

%��ʼֵ
a = 0;%�½�
b = 1;%�Ͻ�
M = 10;

%���
h=(b-a)/(2*M);
s1=0;
s2=0;

for k=1:M
   x=a+h*(2*k-1);
   s1=s1+f(x);
end
for k=1:(M-1)
   x=a+h*2*k;
   s2=s2+f(x);
end

s=h*(f(a)+f(b)+4*s1+2*s2)/3;
