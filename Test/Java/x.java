package ly.hope;



import java.awt.Color;

import java.util.ArrayList;

import java.util.List;

import java.util.Random;



/**

* �����Ա�����

*

* @author CxyLy

*

*/

public class Comment {



/**

* ���ۼ���

*/

static List<String> commentList = new ArrayList<String>();

// ��ʼ������

static {

commentList.add("С����ǸϽ��µ���");

commentList.add("�պÿ��������л�����Ҽ۸�Ҳ���ˡ�");

commentList.add("��ķ��� �õ�����");

commentList.add("С����ͼ���ܺÿ����͵Ĺ���Ҳ��Ư�����ܴ��Ʒǳ��ú��д��⣬");

commentList.add("������ƣ��и��ӵĺ��ӻᾭ��Ū����������ƾͲ����ڶ�ʧ�ˣ���������");

commentList.add("��Ʒ����Ԥ�� �������ϻ�����ʵ ϣ����Ҫ��ʲô���϶��ü���");

commentList.add("�ܺõ�������������ĺ�ʵ��ˮ�����ֱ����������������˹��ã����㣬ʡ�簡����ݸ��� ");

commentList.add("���ڶ������ʣ�ʳ�ĺ����ʣ��ڸзḻ�ڸ����ڣ��������㣬��±����ʮ�ֽ���������С��װ���ɾ����������㴢�棬����С��װ���ɾ�������");

commentList.add("���㴢�棬���������ĺܹ�񫣬�ݳ�������ɫ��ζ��ȫ�����������ĺܹ��룬");

commentList.add("���ǺóԵ�ͣ�����������ϵ�ζ��Ҳ��Ũ������������������������Ϸ�û��������ĺܺó�Ŷ���Ƽ�����");

commentList.add("���ˣ����˼���ܲ����ܽ�ʵ��ʱ���������綯����������������ˣ��۸���ʵ��");

commentList.add("�����ܼ�ʱ���۸���ˣ������ȽϺã�������ʵ�����˺ܶ࣬����2��Կ�ף��ͷ�����Ϣ�ܿ죬�����Ʒ�����ģ��Բ�Ʒ�Ƚ���Ϥ���յ��Ժ���ͷ������һ���������");

commentList.add("ʳ����ָ�ܹ����������������������������󣬲��������������������ʡ���������ԣ��ܹ������˵����������������������ӳ������ʳ�֮Ϊʳ�");

commentList.add(

"ʳ��ͨ������̼ˮ�����֬���������ʡ�ˮ���ɣ��ܹ����ʳ��������Ϊ������������ṩӪ�������õ����ʡ�ʳ�����Դ������ֲ�����������������������������򷢽Ͳ�Ʒ���Ǿƾ���������ɲɼ������֡����������ԡ����Ե�����ֲ�ͬ�ķ�ʽ���ʳ�");

commentList.add("ʳ���ˮ������ÿ��ı���Ʒ��");

commentList.add("��ʷ�ǡ����²����д������������������Ӵ���� Ӧ�� ʳ������񡣡�");

commentList.add("�����顤Τ�봫�������z�۩{�˴� �� ����ʳ���");

commentList.add("����ʮ��Ŀ��֮����״����ʮ���أ�����һ��˽����ר�ŷ�����ѻƬ������װ��̳�����棬���˿ڣ�ճ�˲�ʳ�����ֽ������ʳ��֮�ࡣ��");

commentList.add("���ᡶ�����㡤���ֵ����졷������Щ���ܡ�Ұ���ǡ���������ʱ��͵�ܵ�ׯ�ڵ�����Ѱʳ���");

commentList.add("�����䡶�ۺ⡤�̳桷�����临֮�ң����䣨ʳ�ȳ棩ϣ��������ʳ���ν֮�֡���");

commentList.add("�����顤����־�¡����� ����ͬ������ȣ������ɖ�Ҷ�Ծ����� ���� ���ס��ɺ�Ի����ʳ»����ʥ���������Գ棬��������˶�ʳ����Ҳ������ʱ����������Ϊ�����������£�����ʳ��֮ӦҲ����");

commentList.add("ũҵ�ĳ�����������������Դ���ڴ�֮ǰ������ʳ����Դ���������ԺͲɼ���������Ҫ��Ұ��ֲ��Ͷ����ṩ�Ķ���Ϊת��");

commentList.add("������������������ڲɼ����õĻ����Ϻͳ�������ʵ���У��𲽹۲����Ϥ��ĳЩֲ����������ɣ���������������������");

commentList.add("���Ӻܺã���װʦ��˵Ҳ�������ñ����ǹ涨���Ļ�������ͨ�ļ�Ǯ����ֵĺܺã�����");

commentList.add("����ȥ�ǳ���ʵ��ϴ�»�����ʽ�ÿ�������Ҳ�죬ϴ����7.8���·�û������");

commentList.add("˳���ͻ�����������ܺá��ܺ��ò�ռ�ط�������Ҳ����һ����ϴ6�������·���������");

commentList.add("֪������");

commentList.add("��̶Ҷ���֪��");

commentList.add("�ֻ���ɽ");

commentList.add("��������");

commentList.add("����֮Լ");

commentList.add("��ס֪��");

commentList.add("û���˱���������");

commentList.add("��������ʹ");

commentList.add("������ ������");

commentList.add("���Ӽ��ڶ�");

commentList.add("��ɮ");

commentList.add("�кܶ�");

commentList.add("����Ա");

commentList.add("����");

commentList.add("д��ҵ");

commentList.add("�ָ��¶�");

commentList.add("ߢȡ�˼�״��");

commentList.add("Ψ�и��ķ�����");

commentList.add("���������һ����");

commentList.add("�������");

commentList.add("ǧ��ӣ");

commentList.add("sakura");

commentList.add("��Ӫ����");

commentList.add("������");

commentList.add("������");

commentList.add("����Ʈ��ˮ����");

commentList.add("��˹��");

commentList.add("������");

commentList.add("��������");

commentList.add("�����ǲ�׬");



}



/**

* ��ʾ����

*/

public static void showComment() {

StringBuffer end_comment = new StringBuffer(100);

StringBuffer end_se = new StringBuffer(100);

Random random = new Random();



while (end_comment.length() < 120 || end_se.length() < 120) {

end_comment.append(commentList.get(random.nextInt(commentList.size())));

end_se.append(commentList.get(random.nextInt(commentList.size())));

}

// System.out.println(end_se.length());

System.out.println(end_comment);

System.out.println();

System.out.println(end_se);

}



public static void main(String[] args) {



System.out.println("ִ�п�ʼ");

// ���� ����

showComment();



// ͼƬ

String path = "C:\\Users\\CxyLy\\Desktop\\";



Hope.markImageByText(Math.random() + "", path + "files\\1.jpg", path + "1.jpg", 0, new Color(0, 0, 0), "JPG");

Hope.markImageByText(Math.random() + "", path + "files\\2.jpg", path + "2.jpg", 0, new Color(0, 0, 0), "JPG");

Hope.markImageByText(Math.random() + "", path + "files\\3.jpg", path + "3.jpg", 0, new Color(0, 0, 0), "JPG");

Hope.markImageByText(Math.random() + "", path + "files\\4.jpg", path + "4.jpg", 0, new Color(0, 0, 0), "JPG");

Hope.markImageByText(Math.random() + "", path + "files\\5.jpg", path + "5.jpg", 0, new Color(0, 0, 0), "JPG");



System.out.println("ִ�����");

}



}



