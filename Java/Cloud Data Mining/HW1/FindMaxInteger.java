import java.io.IOException;
import java.util.Arrays;

import org.apache.hadoop.conf.*;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.*;
import org.apache.hadoop.mapred.*;
import org.apache.hadoop.mapreduce.*;
import org.apache.hadoop.util.*;
import org.w3c.dom.Text;

import jdk.javadoc.doclet.Reporter;


public class FindMaxInteger {
    // Mapper
    public static class IntMapper extends MapReduceBase implements Mapper<LongWritable, /* Input key Type */
            Text, /* Input value Type */
            Text, /* Output key Type */
            IntWritable> /* Output value Type */
    {

        public void map(LongWritable key, Text value, OutputColl

            Text word = new Text();
            word.set("1");
            output.collect(word, new IntWritable(number));
        }

    }

    public static class E_EReduce extends MapReduceBase implements Reducer<Text, IntWritable, Text, IntWritable> {
        int[] max = { Integer.MIN_VALUE, Integer.MIN_VALUE, Integer.MIN_VALUE, Integer.MIN_VALUE, Integer.MIN_VALUE };

        public void reduce(Text key, Iterator<IntWritable> values, OutputCollector<Text, IntWritable> output,
                Reporter reporter) throws IOException {
            

            while (values.hasNext()) {

                int value = values.next().get();

                if (value > max[0]) { // Finding max value

                    max[0] = value;
                    Arrays.sort(max);

                }
            }
            for (int i : max) {
                output.collect(key, new IntWritable(i));
            }
            
        }
    }

    public static void main(String[] args) throws Exception {
        JobConf conf = new JobConf(FindMaxInteger.class);
        conf.setJobName("FindMaxInteger");

        conf.setOutputKeyClass(Text.class);
        conf.setOutputValueClass(IntWritable.class);

        conf.setMapperClass(IntMapper.class);
        // conf.setCombinerClass(Reduce.class);
        conf.setReducerClass(E_EReduce.class);

        conf.setInputFormat(TextInputFormat.class);
        conf.setOutputFormat(TextOutputFormat.class);

        FileInputFormat.setInputPaths(conf, new Path(args[0]));
        FileOutputFormat.setOutputPath(conf, new Path(args[1]));

        JobClient.runJob(conf);

    }
}
