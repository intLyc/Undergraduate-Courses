function [x] = Zhuigan()
%׷�Ϸ������Խ��߷�����

%Ҫ��ķ�����
a = [4 4 4 4 4];
c = [-1 -1 -1 -1];
d = [-1 -1 -1 -1];
b = [100 0 0 0 200]';

%���
%��ȡ����
n=length(a);
n1=length(c);
n2=length(d);
%��ʼ��
L=zeros(n);
U=zeros(n);
p=1:n;
q=1:n-1;
x=1:n;
y=1:n;
%׷�Ϸ���������
p(1)=a(1);
for i=1:n-1
    q(i)=c(i)/p(i);
    p(i+1)=a(i+1)-d(i)*q(i);
end
%����y
y(1)=b(1)/p(1);
for i=2:n
    y(i)=(b(i)-d(i-1)*y(i-1))/p(i);
end
%����x
x(n)=y(n);
for i=(n-1):-1:1
    x(i)=y(i)-q(i)*x(i+1);
end
%L,U����
for i=1:n
    L(i,i)=p(i);
    U(i,i)=1;
end
for i=1:n-1
    L(i+1,i)=d(i);
	U(i,i+1)=q(i);
end
