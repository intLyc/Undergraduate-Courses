function [x] = Newton21()
%ţ�ٵ��������5����ֵ

%����
y = inline('x^2-5','x');
dy = inline('2*x','x');

%���ó�ʼֵ
P(1) = 2.2;
tol = 10e-9;
max = 1000;

%����
for k = 2:max	
	P(k) = P(k-1)-y(P(k-1))/dy(P(k-1));	
	err = abs(P(k)-P(k-1));
	p = P(k);
	if (err<tol),break,end
end

P = P';

%�����������
x = vpa(p,10);

%��ͼ
px = 2:1/100:3;
%ԭ����
py = px.^2-5;
plot(px,py);
hold on;
%y = 0����
py0 = px*0;
plot(px,py0);
hold on;
%����ĵ�
scatter(x,0);
end
