function [y] = Lagrange_Runge()
%LAGRANGE��ֵ��֤Runge����

%��ʼֵ
x0 = 4.97;
y = [0 0];
X = -5:1:5;
Y = 1./(1+X.^2);

%���
n = length(X);
L = zeros(n,n);
for k = 1:n
    V = 1;
    for j = 1:n
        if k ~= j
            V = conv(V,poly(X(j)))/(X(k)-X(j));
        end
    end
    L(k,:) = V;
end
C = Y*L;

px = -5:1/100:5;
py = 0;
py0 = 0;
for k = 1:n
    py = py+px.^(k-1)*C(n+1-k);
    y(1) = y(1)+x0^(k-1)*C(n+1-k);
end
py0 = 1./(1+px.^2);
y(2) = 1/(1+x0^2);

%��ͼ
%ԭ���ݵ�
scatter(X,Y);
hold on;
%��ֵ���ĺ���
plot(px,py);
hold on;
%ԭ����
plot(px,py0);
hold on;
%����
scatter([x0 x0],y,'g');
end
