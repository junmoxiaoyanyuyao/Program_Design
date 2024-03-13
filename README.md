# 开发文档

## 题签 《程序设计基础课程设计》 （2022级）

### 1、编写一个C 语言程序，实现一个包含素质类项目对应成果管理的成绩管理系统，能够录入学校所有本科生的成绩和素质类项目对应成果，至少能够管理XX条成绩记录。其中：

1）管理系统所管理物品仅包括各种计算机配件。

#### 2）录入成绩记录主要包括：学生学号、学生姓名、成果类型、认定加分值、录入时间等。

#### 3）成果类型分为科研成果和竞赛获奖两类，科研成果分为论文和项目两种。

> 论文信息至少包括：所有作者和顺序（可能有通讯作者）、论文名称、期刊名称/会议名称、发表时间、卷/期/论文号/页码范围（部分信息可能没有）、论文级别信息和加分信息等。

> 项目信息至少包括：所有成员和顺序、指导教师姓名、项目名称、项目编号、立项和结项时间。

> 获奖信息至少包括：竞赛项目名称、主办单位、所有获奖人和顺序（可能没有顺序）、获奖等级、获奖时间。

#### 4）具体数据结构格式、异常处理，待定

### 具体功能要求如下：

#### 1）【增加】能够从文件中录入多条记录，也能够随时录入1 条记录。

> 注意：需要考虑各种类型的不规范、不合理或错误数据，如：部分信息缺失、认定加分值与成果类型不相符等。【重点考察】

#### 2）【修改】能够随时修改1 条记录。【重点考察】

#### 3）【删除】能够随时删除1 条进货/销售记录。

#### 4）【查询】能够按照指定的顺序打印符合要求的成绩信息（按照配件种类检索）。

> 如：查询学号/姓名/某成果类型
> 排序方式

#### 5）【统计】能够统计某名学生认定的总加分 ；能够生成目前的加分排序表。【重点考察】

#### 6）【存储】能够将当前系统中的所有成绩信息按指定的排序顺序导出到.txt/.xls文件中。

#### 7）其它你认为有用的附加功能，可酌情添加。

### 要求

1.请你的团队实现一个包含素质类项目对应成果管理的成绩管理系统，能够录入学校所有本科生的成绩和素质类项目对应成果，并进行管理和维护

2.完成管理系统的设计和实现工作。请按照人性化的方式设计具体功能，如：增加信息仅含有部分数据，灵活的数据输入方式，软件使用人员操作失误，用户希望的多样化的查询和统计方式，清晰美观的输出方式，合理划分为多个源文件

3.自行拟定测试方案，提供充足的测试样例或具体功能测试建议。提前准备充足的原始数据文件用于现场评测，文件类型为txt，每个文件至少包含30条记录。



## 附录

### 计算机科学与技术学院本科生素质类项目加分细则

|   **类型**   | **加分项目**                                   |                                                              | **加分对象**                                                 | **认定加分值** | **备注**                                                     |
| :----------: | ---------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | -------------- | ------------------------------------------------------------ |
| 一、科研成果 | 大学生创新创业计划项目                         | 国家级优秀结题项目                                           | 负责人                                                       | 0.1 GPA        | 学院认定，排名要与立项、中期检查、结题环节一致               |
|              |                                                |                                                              | 第二名                                                       | 0.05 GPA       |                                                              |
|              | 学术论文  （计算机专业领域）                   | 中国计算机学会推荐国际学术会议和期刊目录（最新）  中国科学院文献情报中心期刊分区（最新） | 业界公认学科综合顶级期刊                                     | 0.4 GPA        | 学院认定， 必须是第一作者， 署名第一单位必须是吉林大学计算机科学与技术学院，加分前要求答辩，由推免工作小组组织相关专家认定。 |
|              |                                                |                                                              | l CCF-A期刊  l CCF-A会议长文  l CCF-B会议的最佳论文/最佳学生论文 | 0.2 GPA        |                                                              |
|              |                                                |                                                              | l CCF-B期刊论文  l 中科院期刊分区一区论文  l CCFC会议的最佳论文/最佳学生论文 | 0.1  GPA       |                                                              |
|              |                                                |                                                              | l CCF-C 期刊论文  l CCF-B 会议长文  l 中科院期刊分区二区论文  l 计算机学报、软件学报发表的学术论文 | 0.05  GPA      |                                                              |
|              |                                                |                                                              | l 影响因子非0的SCI检索期刊论文  l CCF-C 会议长文  l 中国科学：信息科学、计算机研究与发展、计算机辅助设计与图形学学报、电子学报中文版、自动化学报发表的学术论文 | 0.02  GPA      |                                                              |
|              |                                                |                                                              | l EI检索期刊                                                 | 0.01  GPA      |                                                              |
| 二、竞赛获奖 | 吉林大学本科学生学科竞赛体系（计算机学科竞赛） | A类竞赛国家级一等奖（金奖）                                  | 赛制要求每组参赛人数不足6人的，认定实际获奖人，超过6人的（含6人），认定前6人，获奖人数每人加分相同。 | 0.4 GPA        | 学院认定， 国际竞赛（洲际比赛）等同于国家级竞赛；设特等奖的赛事， 按照特等对一等的关系顺延；获奖排名以获奖证书为准；以小组形式参赛有明确个人成绩的，按照个人成绩进行排序；以小组参赛无明确个人成绩的，具体排名根据个人贡献，并参考指导教师意见进行排序。 |
|              |                                                | A类竞赛国家级二等奖（银奖）  B类竞赛国家级一等奖（金奖）     | 0.2  GPA                                                     |                |                                                              |
|              |                                                | A类竞赛国家级三等奖（铜奖）  B类竞赛国家级二等奖（银奖）  C类竞赛国家级一等奖（金奖） | 0.1 GPA                                                      |                |                                                              |
|              |                                                | B类竞赛国家级三等奖（铜奖）  C类竞赛国家级二等奖（银奖）     | 0.05  GPA                                                    |                |                                                              |
|              |                                                | C类竞赛国家级三等奖（铜奖）                                  | 0.02  GPA                                                    |                |                                                              |

> 说明：1.同类成果中不累计加分，取代表作的最高加分计入推免综合成绩；

> 2.五大类别间的加分允许累加，但累计加分最高不超过0.4GPA;

> 3.计算机类学科竞赛列表：ACM-ICPC国际大学生程序设计竞赛,中国大学生服务外包创新创业大赛,中国高校计算机大赛（大数据挑战赛）,CCSP大学生计算机系统与程序设计竞赛,全国大学生物联网设计竞赛,CCPC中国大学生程序设计竞赛,全国大学生信息安全竞赛,全国大学生信息安全竞赛（信息安全作品赛；创新实践能力赛）,中国高校计算机大赛（团体程序设计天梯赛，移动应用创新赛，网络技术挑战赛，人工智能创意赛，微信小程序开发赛）,全国大学生数学建模竞赛,美国大学生数学建模竞赛,全国高校密码数学挑战赛，全国大学生数学竞赛（尚未列入计算机类学科竞赛列表的其他竞赛，在学院评审环节酌情认定）;

> 4.非计算机类学科竞赛的A、B、C类奖项的认定加分值对应减半。

> 5.业界公认学科综合顶级期刊是指《CELL》、《NATURE》和《SCIENCE》。

###   程设2018

1、编写一个C 语言程序，实现一个计算机配件的进货/销售管理系统，至少能够
管理30 条进货/销售记录。其中：
1）管理系统所管理物品仅包括各种计算机配件。
2）进货记录主要包括：时间、配件名称、型号、制造商、单价、数量、总
价、供货商等。
3）销售分为批发、零售两种方式。
批发销售记录主要包括：时间、配件名称、型号、制造商、批发单价、数量、
总价、客户信息等。
零售销售记录主要包括：时间、配件名称、型号、制造商、零售单价、数量、
总价、客户信息等。
4）对于“批发数量超过规定数量”、“批发销售总价超过规定额度”的情况，
附赠一件其它配件（系统动态随机列举三种小型配件，以供客户选择其一）。
5）请自行组织相关信息的存储方式和显示格式。
为了简化，特做如下约定：
1）时间仅包括月、日、时、分（默认为当年）。
2）配件种类（即配件名称）最多10 种，每种配件最多5 款不同型号。
3）制造商、供货商、客户（团体、个人）自行设定，尽可能符合实际情况。
提醒：制造商、供货商、客户可能重名。
4）金额要精确到元、角、分，不允许有误差，最高额度不超过1000 万；最
大数量不超过int 允许最大整数。
具体功能要求如下：
0）开始时，管理系统有运行资本500 万元。
1）【增加】能够从文件中录入多条进货/销售记录，也能够随时录入1 条进
货/销售记录。注意：需要考虑各种类型的不规范、不合理或错误数据，如：编
码位数不对、格式不对等。【重点考察】
2）【修改】能够随时修改1 条进货/销售记录。按照财务规范，如需修改错
误的进货/销售记录，应将当前错误进货/销售记录予以退账（包括赠品）后，再
补充添加正确的进货/销售记录。【重点考察】
3）【删除】能够随时删除1 条进货/销售记录。
4）【查询】能够按照合理顺序打印某种配件的进货/销售信息（按照配件种
类检索）。
5）【查询】能够按照合理顺序打印某个供货商的历史进货信息（按照供货商
标识检索）。
6）【查询】能够按照合理顺序打印某个客户的历史采购信息（按照客户标识
检索）。
7）【统计】能够统计营业额（销售总额）、盈利额（销售总额减除销售商品
的进货总额）；能够生成目前的库存报表。【重点考察】
8）【统计】能够统计所有赠品情况。
9）【某段时间范围】能够打印某段时间范围内的所有进货或销售信息。【重
点考察】
10）【存储】能够将当前系统中的所有信息保存到文件中。
11）其它你认为有用的附加功能，可酌情添加。