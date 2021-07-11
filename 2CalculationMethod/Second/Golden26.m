function [out] = Golden26()
%�ƽ�ָ���������ⵥ�庯�� �����䣨0~1���ϵļ���ֵ

%����
f = inline('sin(x)-x^2','x');

%��ʼֵ
a = 0;%�½�
b = 1;%�Ͻ�
delta = 0.00001;
epsilon = delta;

%���
r1 = (sqrt(5)-1)/2;
r2 = r1^2;
h = b-a;
ya = f(a);
yb = f(b);
c = a+r2*h;
d = a+r1*h;
yc = f(c);
yd = f(d);
k = 1;
A(k) = a;
B(k) = b;
C(k) = c;
D(k) = d;
while (abs(yb-ya)>epsilon) | (h>delta)
    k = k+1;
    if (yc>yd)
        b = d;
        yb = yd;
        d = c;
        yd = yc;
        h = b-a;
        c = a+r2*h;
        yc = f(c);
    else
        a = c;
        ya = yc;
        c = d;
        yc = yd;
        h = b-a;
        d = a+r1*h;
        yd = f(d);
    end
    A(k) = a;
    B(k) = b;
    C(k) = c;
    D(k) = d;
end

dp = abs(b-a);
dy = abs(yb-ya);
p = a;
yp = ya;

if (yb>ya)
    p = b;
    yp = yb;
end

G = [A' C' D' B'];
S = [p yp];
E = [dp dy];

out = [p p+dp];
end

